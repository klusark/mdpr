#include "engineLib.hpp"
#include "network.hpp"
#include "SDL/SDL_net.h"
#include "packets.hpp"
#include "packetHandlers.hpp"
#include "stdio.h"
#include <queue>
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


		std::queue<recvdPacket> serverRecvdQueue;
		std::queue<recvdPacket> clientRecvdQueue;


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
				numready = SDLNet_CheckSockets(set, 100000);
				if (numready){
					if (SDLNet_SocketReady(serverSocket)) {
						TCPsocket newSocket = SDLNet_TCP_Accept(serverSocket);
						if (newSocket != 0){

							SDL_CreateThread(network::serverRecvThread, newSocket);
							packet::spritePacket *temp = new(packet::spritePacket);
							temp->type = packet::sprite;
							temp->spriteID = 523;
							memcpy(temp->name, "player", sizeof("player"));
							SDLNet_TCP_Send(newSocket, temp, sizeof(packet::spritePacket));
						}
					}
				}
			}
		}


		
		int serverRecvThread(void *data)
		{
			const static int bufferSize = 1024;
			int length;
			char message[bufferSize];
			TCPsocket socket = static_cast<TCPsocket>(data);
			SDL_CreateThread(serverProsessRecvd, 0);
			for(;;){
				length = SDLNet_TCP_Recv(socket, message, bufferSize);
				if(length <= 0) {
					std::cout<<"error";
					SDLNet_TCP_Close(socket);
					return -1;
				}
				recvdPacket packet;
				packet.message = message;
				packet.length = length;
				serverRecvdQueue.push(packet);
			}
		}

		int clientRecvThread(void *data)
		{
			const static int bufferSize = 1024;
			int length;
			char message[bufferSize];
			TCPsocket socket = static_cast<TCPsocket>(data);
			SDL_CreateThread(clientProsessRecvd, 0);
			for(;;){
				length = SDLNet_TCP_Recv(socket, message, bufferSize);
				if(length <= 0) {
					std::cout<<"error";
					SDLNet_TCP_Close(socket);
					return -1;
				}
				recvdPacket packet;
				packet.message = message;
				packet.length = length;
				clientRecvdQueue.push(packet);
			}
		}

		void limitFPS(short FPS, unsigned int &bticks)
		{
			unsigned int wait = 1000 / FPS;
			unsigned int cticks = SDL_GetTicks();
			if ((cticks - bticks) < wait){
				//framerate exceeded limit....so we wait the difference
				SDL_Delay(wait - (cticks - bticks));
			}
			bticks = SDL_GetTicks();
		}


		int serverProsessRecvd(void *data)
		{
			unsigned int bticks = 0;
			for(;;){
				while (!serverRecvdQueue.empty()){
					recvdPacket temp = serverRecvdQueue.front();
					handlers::serverRecvHandler(temp.message, temp.length);
					serverRecvdQueue.pop();
				}
				limitFPS(60, bticks);
			}
		}

		int clientProsessRecvd(void *data)
		{
			unsigned int bticks = 0;
			for(;;){
				while (!clientRecvdQueue.empty()){
					recvdPacket temp = clientRecvdQueue.front();
					handlers::clientRecvHandler(temp.message, temp.length);
					clientRecvdQueue.pop();
				}
				limitFPS(60, bticks);
			}
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
			SDL_CreateThread(network::clientRecvThread, clientSocket);

			packet::connectPacket *test = static_cast<packet::connectPacket *>(malloc(sizeof(packet::connectPacket)));
			
			test->type = packet::connect;
			memcpy(test->name, "klusark\0aaaaaaaaaaaaaaaaaaaaaaaa", 32);

			int len,result;

			len = sizeof(test);
			result=SDLNet_TCP_Send(clientSocket, test, len);
			free(test);
			if(result < len) {
				printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
				// It may be good to disconnect sock because it is likely invalid now.
			}
			


		}
	}
}
