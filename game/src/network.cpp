#include <ClanLib/core.h>
#include <ClanLib/network.h>
#include "network.hpp"
#include "networkServer.hpp"
#include "networkClient.hpp"

Network::Network()
{
	Server *server = new Server;
	server->runServer();
	Client *client = new Client;
	client->runClient();
}


void Network::update()
{
}



/*namespace engine
{
	namespace network
	{
		//IPaddress serverIp;
		//IPaddress clientIp;

		//TCPsocket serverSocket;
		//TCPsocket clientSocket;

		unsigned short defaultPort = 9999;
		unsigned short port = defaultPort;


		std::queue<recvdPacket> serverRecvdQueue;
		std::queue<recvdPacket> clientRecvdQueue;


		bool initNetwork()
		{
			if(SDLNet_Init() != 0) {
				std::cout<<"Unable to initialize SDL NET: "<< SDLNet_GetError()<<std::endl;
				return false;
			}

			return true;

		}

		void  destoryNetwork()
		{
			//SDLNet_Quit();
		}

		int startServer(void *data)
		{
			if(SDLNet_ResolveHost(&serverIp, NULL, port) != 0) {
				std::cout<<"SDLNet_ResolveHost: "<< SDLNet_GetError()<<std::endl;
				return -1;
			}

			serverSocket = SDLNet_TCP_Open(&serverIp);
			if(!serverSocket) {
				std::cout<<"SDLNet_TCP_Open: "<< SDLNet_GetError()<<std::endl;
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
			return 0;
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
			return 0;
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
			return 0;
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
			return 0;
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
			return 0;
		}


		void connect()
		{
			
			// connect to localhost at port 9999 using TCP (client)

			if(SDLNet_ResolveHost(&clientIp, "localhost", port)==-1) {
				std::cout<<"SDLNet_ResolveHost: "<< SDLNet_GetError()<<std::endl;
				return;
			}

			clientSocket = SDLNet_TCP_Open(&clientIp);
			if(!clientSocket) {
				std::cout<<"SDLNet_TCP_Open: "<< SDLNet_GetError()<<std::endl;
				return;
			}
			SDL_CreateThread(network::clientRecvThread, clientSocket);

			packet::connectPacket *test = new packet::connectPacket;
			
			test->type = packet::connect;
			memcpy(test->name, "klusark", 32);

			int len,result;

			len = sizeof(test);
			result=SDLNet_TCP_Send(clientSocket, test, len);
			delete test;
			if(result < len) {
				std::cout<<"SDLNet_TCP_Send: "<< SDLNet_GetError()<<std::endl;
				// It may be good to disconnect sock because it is likely invalid now.
			}
			


		}
	}
}
*/
