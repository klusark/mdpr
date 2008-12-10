#include <ClanLib/core.h>
#include <ClanLib/network.h>
#include <iostream>
#include "network.hpp"
#include "networkServer.hpp"

bool Network::Server::runServer()
{

	try{
		netsession = new CL_NetSession("MDPR");
		slotConnect =		netsession->sig_computer_connected()		.connect(this, &Network::Server::onConnect);
		slotDisconnect =	netsession->sig_computer_disconnected()	.connect(this, &Network::Server::onDisconnect);

		netsession->start_listen("4323");
		std::cout << "Server Started" << std::endl;
	}catch (CL_Error err){
		std::cout << "Fatal server error: " << err.message.c_str() << std::endl;
	}


	return true;
}

void Network::Server::onConnect(CL_NetComputer &computer)
{
	std::cout << "Client joined." << std::endl;
}

void Network::Server::onDisconnect(CL_NetComputer &computer)
{
	std::cout << "Client disconnected." << std::endl;
}
