#include <boost/asio.hpp>
#include <boost/crc.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

//#include <ClanLib/core.h>
//#include <ClanLib/network.h>

#include <iostream>

#include "network.hpp"
#include "networkClient.hpp"
#include "packets.hpp"
#include "../sprite/spriteManager.hpp"
using boost::asio::ip::udp;
struct thread
{
public:
	thread(boost::asio::io_service &ioService) 
		: ioService(ioService)
	{}
	void operator()(){
		for (;;){
			try
			{
				ioService.run();
			}
			catch (...)
			{
				
			}
			
		}
		return;
	}
private:
	boost::asio::io_service& ioService;
};

Network::Client::Client() : socket(ioService)
{
	udp::resolver resolver(ioService);

	udp::resolver::query query(udp::v4(), "127.0.0.1", "5000");
	udp::resolver::iterator iterator = resolver.resolve(query);

	receiver_endpoint = *resolver.resolve(query);
	socket.open(udp::v4());

	socket.async_receive_from(boost::asio::buffer(buffer), receiver_endpoint, boost::bind(&Network::Client::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	thread threads(ioService);
	boost::thread test(threads);
}

Network::Client::~Client()
{
}

bool Network::Client::runClient()
{
	try
	{
		connectPacket *packet = new connectPacket;
		packet->packetID = connectPacketID;
		packet->nameLength = 7;
		strcpy(packet->name, "klusark");
		
		//boost::asio::const_buffer test((const void *)tset, 4);
		socket.send_to(boost::asio::buffer((const void *)packet, 13), receiver_endpoint);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
		return false;
	}
	return true;
}

void Network::Client::onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd)
{
	socket.async_receive_from(boost::asio::buffer(buffer), receiver_endpoint, boost::bind(&Network::Client::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	if (bytesRecvd == 0){
		return;
	}
	packetIDs packetID;
	memcpy(&packetID, buffer, 4);
	switch(packetID)
	{
	case spritePacketID:
		{
			spritePacket *packet = (spritePacket *)buffer;
			sprite->registerSprite("player", packet->name);
		}
		break;
	default:
		std::cout << "errorzor" << std::endl;
		break;

	}
	
}


/*void Network::Client::onReciveSprite(CL_NetPacket &packet, CL_NetComputer &computer)
{

	//sprite->registerSprite(packet.input.read_string(), packet.input.read_string());

}

void Network::Client::onReciveSpriteUpdatePos(CL_NetPacket &packet, CL_NetComputer &computer)
{
	std::string name = packet.input.read_string();
	float x = packet.input.read_float32();
	float y = packet.input.read_float32();
	sprite->Sprites[name]->setX(x);
	sprite->Sprites[name]->setY(y);

}

void Network::Client::onReciveSpriteUpdateAccel(CL_NetPacket &packet, CL_NetComputer &computer)
{
	std::string name = packet.input.read_string();
	float xAccel = packet.input.read_float32();
	float yAccel = packet.input.read_float32();
	sprite->Sprites[name]->setXAccel(xAccel);
	sprite->Sprites[name]->setYAccel(yAccel);
}

void Network::Client::onReciveSpriteUpdateVelocity(CL_NetPacket &packet, CL_NetComputer &computer)
{
	std::string name = packet.input.read_string();
	float xVelocity = packet.input.read_float32();
	float yVelocity = packet.input.read_float32();
	//sprite->Sprites[name]->setXVelocity(xAccel);
	//sprite->Sprites[name]->setYAccel(yAccel);
}

void Network::Client::onDisconnect(CL_NetComputer &computer)
{
	std::cout << "Lost connection to server." << std::endl;
}
*/
