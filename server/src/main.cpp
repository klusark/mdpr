#include "network/networkServer.hpp"

int main()
{
	try {
		Network::Server server;
	}catch(std::exception& e){
		std::cout << "Exception: " << e.what() << "\n";
	}
}
