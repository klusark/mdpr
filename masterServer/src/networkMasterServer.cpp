//#include <boost/asio.hpp>
//#include <boost/bind.hpp>
#include "helpers.hpp"
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/shared_ptr.hpp>

#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/Message.h"
#include "Poco/NObserver.h"
#include <Poco/Thread.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>


//#include <iostream>
//#include <map>
//#include <vector>
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
	socketAddress = Poco::Net::SocketAddress("0.0.0.0", port);
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
	socket.receiveFrom(buffer, BUFFER_SIZE, socketAddress);

	packetIDs packetID;
	memcpy(&packetID, buffer, 4);
	switch(packetID)
	{
	case serverInfoPacketID:
		{
			serverInfoPacket *packet = (serverInfoPacket *)buffer;	
			if (packet->port < 1024){
				break;
			}
			bool fullBreak = false;
			
			unsigned char IP[4];
			memcpy(IP, socketAddress.addr()->sa_data+2, 4);
			for (unsigned int i = 0; i < serverList.size(); ++i){
				if (memcmp((void *)IP, (void *)&serverList[i].ip, 4) == 0){
					if (packet->port == serverList[i].port){
						fullBreak = true;
						break;
					}
				}
			}
			if (fullBreak){
				break;
			}
			logger().information("Added new server: " + socketAddress.toString());
			serverEntry newEntry;
			memcpy(newEntry.ip, IP, 4);

			newEntry.port = packet->port;
			serverList.push_back(newEntry);
			
			break;
		}
		break;
	case getServersPacketID:
		{
			serversListPacket *packets;
			logger().information("Query From: " + socketAddress.toString());

			unsigned int numPackets = int(ceil(float(serverList.size())/32));
			packets = new serversListPacket[numPackets];
			//packet.packetID = serversListPacketID;
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
