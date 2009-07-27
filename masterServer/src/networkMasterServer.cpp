#include <Poco/NObserver.h>
#include <Poco/Thread.h>
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>

#include <sstream>

#include <cmath>

#include "networkMasterServer.hpp"
#include "RequestHandlerFactory.hpp"
#include "RequestHandleFunctions.hpp"
#include "network/packets.hpp"

//Use the Poco::Util::Application main macro
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
	//load default configuration files, if present
	loadConfiguration();
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

	// run the reactor in its own thread so that we can wait for a termination request
	Poco::Thread thread;
	thread.start(reactor);

	FillMap();
	// start the http server
	Poco::Net::ServerSocket svs(80);
	// set-up a HTTPServer instance
	Poco::Net::HTTPServer srv(new RequestHandlerFactory, svs, new Poco::Net::HTTPServerParams);
	srv.start();

	// wait for CTRL-C or kill
	waitForTerminationRequest();
	// Stop the SocketReactor
	reactor.stop();
	//wait for the thread to finish
	thread.join();

	//Return that everything was fine
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
				std::stringstream ss;
				ss << packet->port;
				std::string stringPort = ss.str();
				//Tell the log
				logger().warning("A server at: " + socketAddress.toString() + " tried to list the port: " + stringPort);
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
			//Inform the user of the new server that has been added
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
			//Inform the user of the query from a game client
			logger().information("Query From: " + socketAddress.toString());

			//calculate the number of packets that will be needed
			unsigned int numPackets = int(ceil(float(serverList.size())/numberOfPacketInServerListPacket));
			//Create all the packets
			packets = new serversListPacket[numPackets];
			//Loop though the packets and fill them with information
			for (unsigned int x = 0; x < numPackets; ++x){
				unsigned int end = (x+1) * numberOfPacketInServerListPacket;
				if ((x + 1) * numberOfPacketInServerListPacket > serverList.size()){
					end = serverList.size();
				}
				for (unsigned int i = x * numberOfPacketInServerListPacket; i < end; ++i){
					memcpy((void *)&packets[x].serverList[i - x * numberOfPacketInServerListPacket], (void *)&serverList[i], 6);
				}
				packets[x].packetID = serversListPacketID;
				packets[x].numServers = end - x * numberOfPacketInServerListPacket;
				socket.sendTo((const void *)&packets[x], sizeof(serversListPacket), socketAddress);
			}
			//free the packets from memory
			delete[] packets;
			
		}
		break;
	default:
		//The magic number on the packet does not match any know magic number
		logger().warning("Unknown packet received");
		break;

	}
}
