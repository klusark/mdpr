#include "network.hpp"
#include "sdl/SDL_net.h"
namespace engine
{
	namespace network
	{
		IPaddress serverIp;
		IPaddress clientIp;

		TCPsocket serverSocket;
		TCPsocket clientSocket;

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

		void startServer()
		{


			if(SDLNet_ResolveHost(&serverIp, NULL, 9999) != 0) {
				printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
				return;
			}

			serverSocket = SDLNet_TCP_Open(&serverIp);
			if(!serverSocket) {
				printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
				return;
			}

		}
		void connect()
		{
			
			// connect to localhost at port 9999 using TCP (client)


			if(SDLNet_ResolveHost(&clientIp,"localhost",9999)==-1) {
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
