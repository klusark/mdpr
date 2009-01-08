#ifndef networkServer_hpp
#define networkServer_hpp

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

#include "network.hpp"

class genericSprite;
class spriteManager;

class Network::Server
{
public:
	Server();
	~Server();
	bool runServer();
protected:
	boost::asio::io_service ioService;
	boost::asio::ip::udp::socket serverSocket;
	//std::vector<char> buffer;
	char buffer[512];
	boost::asio::ip::udp::endpoint endpoint;
	boost::asio::deadline_timer timer;

	void onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd);

	void onSpriteUpdate(const boost::system::error_code& error);


	unsigned short posUpdate;

	boost::shared_ptr<spriteManager> ServerSpriteManager;

	unsigned short maxPlayers;
	unsigned short currentPlayers;

	class playerInfo
	{
	public:
		std::string name;
		boost::shared_ptr<genericSprite> sprite;
		boost::asio::ip::udp::endpoint endpoint;


	};

	typedef std::vector<boost::shared_ptr<playerInfo> > playerContainer;
	playerContainer Players;


};

#endif
