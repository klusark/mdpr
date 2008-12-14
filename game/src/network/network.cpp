#include <ClanLib/core.h>
#include <ClanLib/network.h>
#include "network.hpp"
#include "networkServer.hpp"
#include "networkClient.hpp"
#include "../sprite/spriteManager.hpp"

Network::Network(spriteManager *sprite)
{
	Server *server = new Server;
	server->runServer();
	Client *client = new Client(sprite);
	client->runClient();
}

Network::~Network()
{
}

void Network::update()
{
}
