#include "engineLib.hpp"
#include "network.hpp"
#include "SDL/SDL_net.h"
#include "packets.hpp"
#include "packetHandlers.hpp"
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


		std::queue<recvdPacket> recvdQueue;


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

							SDL_CreateThread(network::sendThread, newSocket);
							SDL_CreateThread(network::recvThread, newSocket);
						}
					}
				}
			}
//			return 0;
		}

		int sendThread(void *data)
		{
			TCPsocket socket = static_cast<TCPsocket>(data);
			return 0;
		}

		
		int recvThread(void *data)
		{
			const static int bufferSize = 1024;
			int length;
			char message[bufferSize];
			TCPsocket socket = static_cast<TCPsocket>(data);
			SDL_CreateThread(prosessRecvd, 0);
			for(;;){
				length = SDLNet_TCP_Recv(socket, message, bufferSize);
				if(length <= 0) {
					std::cout<<"error";
					SDLNet_TCP_Close(socket);
					return -1;
					// An error may have occured, but sometimes you can just ignore it
					// It may be good to disconnect sock because it is likely invalid now.
				}
				recvdPacket packet;
				packet.message = message;
				packet.length = length;
				recvdQueue.push(packet);
			}


//			return 0;
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


		int prosessRecvd(void *data)
		{
			unsigned int bticks = 0;
			for(;;){
				
				while (!recvdQueue.empty()){
					recvdPacket temp = recvdQueue.front();
					handlers::recvHandler(temp.message, temp.length);
					recvdQueue.pop();

				}
				limitFPS(60, bticks);



			}
//			return 0;
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
			packet::connectPacket *test = new packet::connectPacket;
			test->type = packet::connect;
			strcpy(test->name, "klusark");

			int len,result;

			len = sizeof(packet::connectPacket);
			result=SDLNet_TCP_Send(clientSocket, test, len);
			//SDL_Delay(500);
			result=SDLNet_TCP_Send(clientSocket, test, len);
			result=SDLNet_TCP_Send(clientSocket, test, len);
			if(result < len) {
				printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
				// It may be good to disconnect sock because it is likely invalid now.
			}


		}
	}
}
