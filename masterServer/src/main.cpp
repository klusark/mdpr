//#include <boost/shared_ptr.hpp>
#include "networkMasterServer.hpp"
#include <signal.h>
#include <Poco/SharedPtr.h>

Poco::SharedPtr<NetworkMasterServer> masterServer;

void signalHandler(int sig)
{
	masterServer->stopServer();
}

int main()
{
	masterServer = Poco::SharedPtr<NetworkMasterServer>(new NetworkMasterServer());

	signal(SIGABRT, &signalHandler);
	signal(SIGTERM, &signalHandler);
	signal(SIGINT, &signalHandler);

	masterServer->runServer();
}
