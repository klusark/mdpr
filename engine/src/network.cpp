#include "engineLib.hpp"
#include "network.hpp"
#include "sdl/SDL_net.h"
#include <iostream>
namespace engine
{
	namespace network
	{
		IPaddress serverIp;
		IPaddress clientIp;

		TCPsocket serverSocket;
		TCPsocket clientSocket;

		unsigned short defaultPort = 9999;
		unsigned short port = defaultPort;

		bool initNetwork()
		{
			if(SDLNet_Init() != 0) {
				printf("Unable to initialize SDL NET: %s\n", SDLNet_GetError());
				return false;
			}

			return true;

		}

		void  destoryNetwork()
		{
			SDLNet_Quit();
		}

		int startServer(void *data)
		{
			if(SDLNet_ResolveHost(&serverIp, NULL, port) != 0) {
				printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
				return -1;
			}

			serverSocket = SDLNet_TCP_Open(&serverIp);
			if(!serverSocket) {
				printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
				return -1;
			}

			SDLNet_SocketSet set = SDLNet_AllocSocketSet(2);
			SDLNet_TCP_AddSocket(set, serverSocket);
			int numready;
			for(;;){
				numready = SDLNet_CheckSockets(set, 1000);
				if (numready){
					if (SDLNet_SocketReady(serverSocket)) {
						if (SDLNet_TCP_Accept(serverSocket) != 0){
							std::cout<<"est";
						}
					}
				}
			}
			return 0;
		}

		void connect()
		{
			
			// connect to localhost at port 9999 using TCP (client)

			if(SDLNet_ResolveHost(&clientIp, "localhost", port)==-1) {
				printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
				return;
			}

			clientSocket = SDLNet_TCP_Open(&clientIp);
			if(!clientSocket) {
				printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
				return;
			}

		}
	}
}
