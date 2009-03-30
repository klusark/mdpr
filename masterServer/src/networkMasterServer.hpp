#ifndef networkMasterServer_hpp
#define networkMasterServer_hpp

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

class networkMasterServer
{
public:
	networkMasterServer();
	~networkMasterServer();
	bool runServer();
protected:
	static boost::asio::io_service ioService;
	boost::asio::ip::udp::socket serverSocket;
	char buffer[512];
	boost::asio::ip::udp::endpoint endpoint;

	void onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd);

	void handleSendTo(const boost::system::error_code& error, size_t bytes_sent);

};
extern boost::shared_ptr<networkMasterServer> masterServer;

#endif // ifndef networkMasterServer_hpp
