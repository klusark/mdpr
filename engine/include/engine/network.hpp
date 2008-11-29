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
		int sendThread(void *data);
		int recvThread(void *data);
	}
}
#endif
