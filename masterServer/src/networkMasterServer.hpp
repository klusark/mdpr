#ifndef networkMasterServer_hpp
#define networkMasterServer_hpp

//#include <boost/asio.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/thread.hpp>
#include "network/packets.hpp"
//using boost::asio::ip::udp;
#include <vector>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/AutoPtr.h>
#include <Poco/Util/ServerApplication.h>

class NetworkMasterServer : public Poco::Util::ServerApplication
{
public:
	NetworkMasterServer();
	~NetworkMasterServer();
	int main(const std::vector<std::string>& args);
	void stopServer();
protected:
	//boost::asio::io_service ioService;
	//udp::socket serverSocket;

	//udp::endpoint endpoint;
	//boost::thread_group ioThreads;

	void onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf);
	void initialize(Poco::Util::Application& self);

	//void handleSendTo(const boost::system::error_code& error, size_t bytes_sent);

	void ioServiceThread();

	typedef std::vector<serverEntry> serverListContainer;
	serverListContainer serverList;

	static const unsigned short numIOServiceThreads = 5;

	enum
	{
		BUFFER_SIZE = 256
	};
	
	Poco::Net::SocketAddress socketAddress;
	Poco::Net::DatagramSocket socket;
	char* buffer;

};

#endif // #ifndef networkMasterServer_hpp
