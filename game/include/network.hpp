#ifndef network_hpp
#define network_hpp
#if _MSC_VER > 1000
#pragma once
#endif

class Network
{
public:
	Network();
	~Network(){}
	void update();
	class Server;
	class Client;

	
};

/*
namespace engine
{
	namespace network
	{
		extern unsigned short defaultPort;
		extern unsigned short port;
		bool initNetwork();
		void destoryNetwork();
		int startServer(void *data);
		void connect();
		int serverProsessRecvd(void *data);
		int clientProsessRecvd(void *data);
		int serverRecvThread(void *data);
		int clientRecvThread(void *data);
		struct recvdPacket
		{
			int length;
			char *message;
		};
	}
}*/
#endif
