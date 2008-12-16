#include <ClanLib/core.h>
#include <ClanLib/network.h>
#include <iostream>
#include <map>
#include "network.hpp"
#include "networkServer.hpp"
#include "../sprite/spriteManager.hpp"
#include "../sprite/genericSprite.hpp"

Network::Server::Server()
{
	sprite = new spriteManager;
	posUpdate = 0;
}

Network::Server::~Server()
{
	delete sprite;
	delete netsession;
}

bool Network::Server::runServer()
{

	try{
		netsession = new CL_NetSession("MDPR");
		slotReciveConnect =	netsession->sig_netpacket_receive("connect").connect(this, &Network::Server::onReciveConnect);
		slotConnect =		netsession->sig_computer_connected()		.connect(this, &Network::Server::onConnect);
		slotDisconnect =	netsession->sig_computer_disconnected()		.connect(this, &Network::Server::onDisconnect);

		netsession->start_listen("4323");
		std::cout << "Server Started" << std::endl;
	}catch (CL_Error err){
		std::cout << "Fatal server error: " << err.message.c_str() << std::endl;
	}
	timerSpriteUpdate = CL_Timer(100);
	slotSpriteUpdate = timerSpriteUpdate.sig_timer().connect(this, &Network::Server::onSpriteUpdate);
	timerSpriteUpdate.enable();


	return true;
}

void Network::Server::onSpriteUpdate()
{
	sprite->update();
	for(spriteManager::spriteContainer::iterator it = sprite->Sprites.begin(); it != sprite->Sprites.end(); ++it){
		CL_SharedPtr<genericSprite> currentSprite = it->second;
		if (posUpdate == 4){
			CL_NetPacket spriteUpdatePosPacket;

			spriteUpdatePosPacket.output.write_string(currentSprite->name);
			spriteUpdatePosPacket.output.write_float32(currentSprite->getX());//x
			spriteUpdatePosPacket.output.write_float32(currentSprite->getY());//y

			netsession->get_all().send("spriteUpdatePos", spriteUpdatePosPacket);
			posUpdate = 0;
		}

		CL_NetPacket spriteUpdateAccelPacket;

		spriteUpdateAccelPacket.output.write_string(currentSprite->name);
		spriteUpdateAccelPacket.output.write_float32(currentSprite->getXAccel());//x
		spriteUpdateAccelPacket.output.write_float32(currentSprite->getYAccel());//y

		netsession->get_all().send("spriteUpdateAccel", spriteUpdateAccelPacket);


		CL_NetPacket spriteUpdateVelocityPacket;

		spriteUpdateVelocityPacket.output.write_string(currentSprite->name);
		spriteUpdateVelocityPacket.output.write_float32(10.0f);//x
		spriteUpdateVelocityPacket.output.write_float32(100.0f);//y

		netsession->get_all().send("spriteUpdateVelocity", spriteUpdateVelocityPacket);
				
	}
	++posUpdate;
	
}

void Network::Server::onReciveConnect(CL_NetPacket &packet, CL_NetComputer &computer)
{
	std::string name = packet.input.read_string();
	std::cout << "asdf" << std::endl;
	sprite->registerSprite("player", name);
	CL_NetPacket spritePacket;
	spritePacket.output.write_string(name);
	spritePacket.output.write_string("player");
	computer.send("sprite", spritePacket);
}

void Network::Server::onConnect(CL_NetComputer &computer)
{
	std::cout << "Client joined." << std::endl;
}

void Network::Server::onDisconnect(CL_NetComputer &computer)
{
	std::cout << "Client disconnected." << std::endl;
}
