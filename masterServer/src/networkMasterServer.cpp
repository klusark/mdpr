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

boost::asio::io_service networkMasterServer::ioService;

networkMasterServer::networkMasterServer() 
	:	serverSocket(ioService, udp::endpoint(udp::v4(), 9937))
{

	serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&networkMasterServer::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));


}

networkMasterServer::~networkMasterServer()
{
}

bool networkMasterServer::runServer()
{
	
	std::cout << "Server Started" << std::endl;
	ioService.run();

	return true;
}

void networkMasterServer::onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd)
{

	packetIDs packetID;
	memcpy(&packetID, buffer, 4);
	switch(packetID)
	{
	case serverInfoPacketID:
		{
			//serverInfoPacket *packet = (serverInfoPacket *)buffer;
			boost::asio::ip::address_v4::bytes_type tests = endpoint.address().to_v4().to_bytes();
			unsigned char ip[4];
			memcpy(ip,tests.elems,4);

			break;
		}
		break;
	default:
		std::cout << "Error in packed recved." << std::endl;
		break;

	}

	serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&networkMasterServer::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	
}

void networkMasterServer::handleSendTo(const boost::system::error_code& error, size_t bytes_sent)
{
	if (error){
		//std::cout << error.message() << std::endl;
	}
}
