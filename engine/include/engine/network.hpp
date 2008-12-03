#ifndef network_hpp
#define network_hpp
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
}
#endif
