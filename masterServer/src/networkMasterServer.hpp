#ifndef networkMasterServer_hpp
#define networkMasterServer_hpp

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
using boost::asio::ip::udp;

struct
{
	std::string serverIP;
	unsigned short port;
};

class networkMasterServer
{
public:
	networkMasterServer();
	~networkMasterServer();
	bool runServer();
protected:
	static boost::asio::io_service ioService;
	udp::socket serverSocket;
	char buffer[512];
	udp::endpoint endpoint;

	void onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd);

	void handleSendTo(const boost::system::error_code& error, size_t bytes_sent);

};
extern boost::shared_ptr<networkMasterServer> masterServer;

#endif // ifndef networkMasterServer_hpp
