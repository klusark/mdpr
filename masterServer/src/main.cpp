#include <boost/shared_ptr.hpp>
#include "networkMasterServer.hpp"
#include <signal.h>

boost::shared_ptr<networkMasterServer> masterServer;

void signalHandler(int sig)
{
	masterServer->stopServer();
}

int main()
{
	masterServer = boost::shared_ptr<networkMasterServer>(new networkMasterServer());

	signal(SIGABRT, &signalHandler);
	signal(SIGTERM, &signalHandler);
	signal(SIGINT, &signalHandler);

	masterServer->runServer();
}
