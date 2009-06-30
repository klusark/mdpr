#include "network/networkServer.hpp"

int main()
{
	server = Poco::SharedPtr<NetworkServer>(new NetworkServer());
	server->runServer();
}
