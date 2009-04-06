#ifndef networkServer_hpp
#define networkServer_hpp

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <boost/thread.hpp>

#include "packets.hpp"

using boost::asio::ip::udp;

class genericSprite;
class spriteManager;
class networkServer
{
public:
	networkServer();
	~networkServer();
	bool runServer();
	void disconnect(unsigned short playerID);
protected:
	static boost::asio::io_service ioService;
	boost::asio::ip::udp::socket serverSocket;
	char buffer[512];
	udp::endpoint endpoint;
	boost::asio::deadline_timer spriteUpdateTimer;
	boost::asio::deadline_timer masterServerUpdateTimer;

	void onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd);

	void handleSendTo(const boost::system::error_code& error, size_t bytes_sent);

	void onSpriteUpdate(const boost::system::error_code& error);

	void updateMasterServer(const boost::system::error_code& error);

	boost::thread_group ioThreads;
	boost::asio::strand strand;

	unsigned short posUpdate;

	unsigned short maxPlayers;
	unsigned short currentPlayers;

	serverInfoPacket packetServerInfo;
	udp::endpoint masterServerEndpoint;

	class playerInfo
	{
	public:
		playerInfo():timer(networkServer::ioService){}
		void disconnect(const boost::system::error_code& e);
		std::string name;
		boost::shared_ptr<genericSprite> playerSprite;
		boost::asio::ip::udp::endpoint endpoint;
		boost::asio::deadline_timer timer;


	};

	typedef std::map<unsigned short, boost::shared_ptr<playerInfo> > playerContainer;
	playerContainer Players;


};
extern boost::shared_ptr<networkServer> server;

#endif
