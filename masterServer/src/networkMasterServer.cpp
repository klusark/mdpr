#include <Poco/Logger.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FileChannel.h>
#include <Poco/Message.h>
#include <Poco/NObserver.h>
#include <Poco/Thread.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>

#include <cmath>

#include "networkMasterServer.hpp"
#include "network/packets.hpp"

POCO_SERVER_MAIN(NetworkMasterServer)

NetworkMasterServer::NetworkMasterServer() 
	:	buffer(new char[BUFFER_SIZE])
{	
}

NetworkMasterServer::~NetworkMasterServer()
{
}

void NetworkMasterServer::initialize(Poco::Util::Application& self)
{
	loadConfiguration(); // load default configuration files, if present
	Poco::Util::ServerApplication::initialize(self);
	logger().information("starting up");
}

int NetworkMasterServer::main(const std::vector<std::string>& args)
{
	// get parameters from configuration file
	unsigned short port = (unsigned short) config().getInt("MasterServer.port", 9937);
	Poco::Net::SocketAddress socketAddress("0.0.0.0", port);
	// set-up a server socke
	socket.bind(socketAddress, true);
	// set-up a SocketReactor...
	Poco::Net::SocketReactor reactor;
	reactor.addEventHandler(socket, Poco::NObserver<NetworkMasterServer, Poco::Net::ReadableNotification>(*this, &NetworkMasterServer::onReceivePacket));
	// run the reactor in its own thread so that we can wait for 
	// a termination request
	Poco::Thread thread;
	thread.start(reactor);
	// wait for CTRL-C or kill
	waitForTerminationRequest();
	// Stop the SocketReactor
	reactor.stop();
	thread.join();

	return Application::EXIT_OK;
}

void NetworkMasterServer::onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf)
{
	Poco::Net::SocketAddress socketAddress;
	//Put the packet into the buffer
	socket.receiveFrom(buffer, BUFFER_SIZE, socketAddress);

	packetIDs packetID;
	//Copy the first 4 bytes out of the buffer for use in identifying the packet
	memcpy(&packetID, buffer, 4);
	switch(packetID)
	{
	case serverInfoPacketID:
		{
			serverInfoPacket *packet = (serverInfoPacket *)buffer;
			//Check if the port is below 1024 and if it is, disallow it
			if (packet->port < 1024){
				char charPort[6];
				//copy the port into a char string
				sprintf(charPort, "%d", packet->port);
				//Tell the log
				logger().warning("A server at: " + socketAddress.toString() + " tried to list the port: " + charPort);
				return;
			}
			
			unsigned char IP[4];
			//copy the ip address into an array
			memcpy(IP, socketAddress.addr()->sa_data+2, 4);
			//loop though the server list
			for (unsigned int i = 0; i < serverList.size(); ++i){
				//and check for any dupelicates
				if (memcmp((void *)IP, (void *)&serverList[i].ip, 4) == 0){
					//make sure that the port is also the same.
					if (packet->port == serverList[i].port){
						//it is so ignore the packet
						return;
					}
				}
			}
			logger().information("Added new server: " + socketAddress.toString());
			serverEntry newEntry;
			memcpy(newEntry.ip, IP, 4);

			newEntry.port = packet->port;
			//add the new server into the list
			serverList.push_back(newEntry);
			
		}
		break;
	case getServersPacketID:
		{
			serversListPacket *packets;
			logger().information("Query From: " + socketAddress.toString());

			unsigned int numPackets = int(ceil(float(serverList.size())/32));
			packets = new serversListPacket[numPackets];
			for (unsigned int x = 0; x < numPackets; ++x){
				unsigned int end = (x+1) * 32;
				if ((x + 1) * 32 > serverList.size()){
					end = serverList.size();
				}
				for (unsigned int i = x * 32; i < end; ++i){
					memcpy((void *)&packets[x].serverList[i - x * 32], (void *)&serverList[i], 6);
				}
				packets[x].packetID = serversListPacketID;
				packets[x].numServers = end - x * 32;
				socket.sendTo((const void *)&packets[x], sizeof(serversListPacket), socketAddress);
			}
			
		}
		break;
	default:
		logger().warning("Unknown packet received");
		break;

	}
}
