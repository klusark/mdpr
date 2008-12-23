#include "network.hpp"
#include "networkClient.hpp"
#include "networkServer.hpp"
#include "../sprite/spriteManager.hpp"
#include <ClanLib/core.h>
#include <ClanLib/network.h>

Network::Network()
{;
	Server *server = new Server;
	server->runServer();
	Client *client = new Client();
	client->runClient();
}

Network::~Network()
{
}

void Network::update()
{
}
