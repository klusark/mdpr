#ifndef networkMasterServer_hpp
#define networkMasterServer_hpp

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <boost/thread.hpp>
#include "network/packets.hpp"
using boost::asio::ip::udp;

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
	boost::thread_group ioThreads;

	void onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd);

	void handleSendTo(const boost::system::error_code& error, size_t bytes_sent);

	typedef std::vector<serverEntry> serverListContainer;
	serverListContainer serverList;

};
extern boost::shared_ptr<networkMasterServer> masterServer;

#endif // ifndef networkMasterServer_hpp
