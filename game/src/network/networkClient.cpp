#include <iostream>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <ClanLib/core.h>
#include <ClanLib/network.h>

#include "network.hpp"
#include "networkClient.hpp"
#include "packets.hpp"
#include "../sprite/spriteManager.hpp"

Network::Client::Client()
{
}

Network::Client::~Client()
{
}

bool Network::Client::runClient()
{
	try
	{
		//ioService.run();
		boost::asio::io_service ioService;

		//boost::asio::ip::udp::socket s(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));
		using boost::asio::ip::udp;

		udp::resolver resolver(ioService);
		udp::resolver::query query(udp::v4(), "127.0.0.1", "5000");
		udp::resolver::iterator iterator = resolver.resolve(query);

		udp::endpoint receiver_endpoint = *resolver.resolve(query);
		
		udp::socket socket(ioService);
		socket.open(udp::v4());

		/*std::vector<char> send_buf;
		send_buf.insert(send_buf.begin(), 'a');
		send_buf.insert(send_buf.end(), 'a');
		
		send_buf.clear();
		send_buf.insert(send_buf.end(), 'a');
		socket.send_to(, receiver_endpoint);*/
		connectPacket *tset = new connectPacket;
		tset->packetID = connectPacketID;
		tset->nameLength = 10;
		strcpy(tset->name, "aqwsxcderf");
		
		//boost::asio::const_buffer test((const void *)tset, 4);
		socket.send_to(boost::asio::buffer((const void *)tset, 16), receiver_endpoint);

	}
	catch(CL_Error err)
	{
		std::cout << "Could not create client: " << err.message.c_str() << std::endl;
		return false;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
		return false;
	}
	return true;
}

void Network::Client::onReciveSprite(CL_NetPacket &packet, CL_NetComputer &computer)
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
