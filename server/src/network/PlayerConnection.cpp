#include "PlayerConnection.hpp"

PlayerConnection::PlayerConnection(Poco::Net::SocketAddress &ClientAddress, std::string name, bool noSpriteUpdates, GenericSprite* sprite):
stillAlive(true),
ClientAddress(ClientAddress)
{
	socket.connect(ClientAddress);
	int test = 9001;
	socket.sendTo((const void *)&test, 4, ClientAddress);
}

PlayerConnection::~PlayerConnection()
{
}
