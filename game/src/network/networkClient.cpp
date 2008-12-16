#include <ClanLib/core.h>
#include <ClanLib/network.h>
#include <iostream>
#include "network.hpp"
#include "networkClient.hpp"
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
		//create a new netsession
		netsession = new CL_NetSession("MDPR");
				//connect the disconnect and receive signals to some slots
		slotDisconnect = netsession->sig_computer_disconnected().connect(this, &Client::onDisconnect);
		
		slotReciveSprite =					netsession->sig_netpacket_receive("sprite")					.connect(this, &Network::Client::onReciveSprite);
		slotReciveSpriteUpdatePos =			netsession->sig_netpacket_receive("spriteUpdatePos")		.connect(this, &Network::Client::onReciveSpriteUpdatePos);
		slotReciveSpriteUpdateVelocity =	netsession->sig_netpacket_receive("spriteUpdateVelocity")	.connect(this, &Network::Client::onReciveSpriteUpdateVelocity);
		slotReciveSpriteUpdateAccel =		netsession->sig_netpacket_receive("spriteUpdateAccel")		.connect(this, &Network::Client::onReciveSpriteUpdateAccel);


		//connect to the server (running on the local machine in this case)
		CL_IPAddress server_ip;
		server_ip.set_address("127.0.0.1", "4323");
		netsession->connect(server_ip);
		std::cout << "connected" << std::endl;


		CL_NetPacket connect;
		connect.output.write_string("klusark");

		//do the actual sending, to all the computers connected
		netsession->get_all().send("connect", connect);

		std::cout << "Sent connect" << std::endl;

	}
	catch(CL_Error err)
	{
		std::cout << "Could not create client: " << err.message.c_str() << std::endl;
		return false;
	}
	return true;
}

void Network::Client::onReciveSprite(CL_NetPacket &packet, CL_NetComputer &computer)
{
	sprite->registerSprite(packet.input.read_string(), packet.input.read_string());
	
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