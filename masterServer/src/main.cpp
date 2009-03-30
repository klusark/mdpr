#include <boost/shared_ptr.hpp>
#include "networkMasterServer.hpp"

int main()
{
	masterServer = boost::shared_ptr<networkMasterServer>(new networkMasterServer());
	masterServer->runServer();

}
