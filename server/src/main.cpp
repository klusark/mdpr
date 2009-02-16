#include "network/networkServer.hpp"

int main()
{
	server = boost::shared_ptr<networkServer>(new networkServer());
	server->runServer();
}
