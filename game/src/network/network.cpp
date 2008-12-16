#include <ClanLib/core.h>
#include <ClanLib/network.h>
#include "network.hpp"
#include "networkServer.hpp"
#include "networkClient.hpp"
#include "../sprite/spriteManager.hpp"

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
