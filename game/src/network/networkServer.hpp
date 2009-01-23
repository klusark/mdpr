#ifndef networkServer_hpp
#define networkServer_hpp

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <map>


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
	boost::asio::ip::udp::endpoint endpoint;
	boost::asio::deadline_timer timer;

	void onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd);

	void handleSendTo(const boost::system::error_code& error, size_t bytes_sent);

	void onSpriteUpdate(const boost::system::error_code& error);

	

	unsigned short posUpdate;

	boost::shared_ptr<spriteManager> ServerSpriteManager;

	unsigned short maxPlayers;
	unsigned short currentPlayers;

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
extern networkServer server;

#endif
