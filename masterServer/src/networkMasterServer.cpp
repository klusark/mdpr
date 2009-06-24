#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "helpers.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <map>
#include <vector>


#include "networkMasterServer.hpp"
#include "network/packets.hpp"


boost::shared_ptr<networkMasterServer> masterServer;

networkMasterServer::networkMasterServer() 
	:	serverSocket(ioService, udp::endpoint(udp::v4(), 9937))
{

	serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&networkMasterServer::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	for (short i = 0; i < numIOServiceThreads; ++i){
		ioThreads.create_thread(boost::bind(&networkMasterServer::ioServiceThread, this));
	}
}

networkMasterServer::~networkMasterServer()
{
}

bool networkMasterServer::runServer()
{
	
	std::cout << "Server Started" << std::endl;
	ioThreads.join_all();

	return true;
}

void networkMasterServer::onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd)
{
	if (error){
	}else{

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
				boost::asio::ip::address_v4::bytes_type address = endpoint.address().to_v4().to_bytes();
				for (unsigned int i = 0; i < serverList.size(); ++i){
					if (memcmp((void *)address.elems, (void *)&serverList[i].ip, 4) == 0){
						if (packet->port == serverList[i].port){
							fullBreak = true;
							break;
						}
					}
				}
				if (fullBreak){
					break;
				}

				std::cout << "Added new server: " << (int)address.elems[0] << "." << (int)address.elems[1] << "." <<  (int)address.elems[2] << "." << (int)address.elems[3] << std::endl;
				serverEntry newEntry;
				memcpy(newEntry.ip, address.elems, 4);

				newEntry.port = packet->port;
				serverList.push_back(newEntry);
				
				break;
			}
			break;
		case getServersPacketID:
			{
				serversListPacket *packets;
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
					serverSocket.send_to(boost::asio::buffer((const void *)&packets[x], sizeof(serversListPacket)), endpoint);
				}
				
			}
			break;
		default:
			std::cout << "Error in packed recved." << std::endl;
			break;

		}
	}

	serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&networkMasterServer::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	
}

void networkMasterServer::handleSendTo(const boost::system::error_code& error, size_t bytes_sent)
{
	if (error){
		//std::cout << error.message() << std::endl;
	}
}

void networkMasterServer::ioServiceThread()
{
	try{
		ioService.run();
	}catch (std::exception& e){
		std::cout << "Exception: " << e.what() << std::endl;
	}catch(...){
		std::cout << "Unknown Exception caught" << std::endl; 
	}
	std::cout << "ioServiceThread: Huge error. FIX ME!!!" << std::endl;
}
