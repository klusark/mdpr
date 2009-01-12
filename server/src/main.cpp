#include "network/networkServer.hpp"

int main()
{
	try {
		networkServer server;
	}catch(std::exception& e){
		std::cout << "Exception: " << e.what() << "\n";
	}
}
