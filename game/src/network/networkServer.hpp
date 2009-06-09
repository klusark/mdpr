#ifndef networkServer_hpp
#define networkServer_hpp

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <boost/thread.hpp>
#include <SFML/System/Clock.hpp>

#include "packets.hpp"

using boost::asio::ip::udp;

class genericSprite;
class spriteManager;

//!The server
/*!
A self contained server in a class.
*/
class networkServer
{
public:
	//!The constructor
	/*!
	Constructs the server and sets up the async operations.
	*/
	networkServer();

	//!The deconstructor
	/*!
	Destroys the server.
	*/
	~networkServer();

	/*!
	Waits untill the server is ready to shut down
	*/
	void runServer();
	
protected:
	/*!
	Called when  a packet is received
	\param error if there is an error, this contains the message.
	\param bytesReceived number of bytes received.
	*/
	void onReceivePacket(const boost::system::error_code& error, size_t bytesReceived);

	/*!
	Handles async sending of packets
	\param error if there is an error, this contains the message.
	\param bytesSent number of bytes sent.
	*/
	void handleSendTo(const boost::system::error_code& error, size_t bytesSent);

	void onSpriteUpdate(const boost::system::error_code& error);

	void updateMasterServer(const boost::system::error_code& error);

	void removeIdlePlayers(const boost::system::error_code& error);

	void ioServiceThread();

	void disconnect(unsigned short playerID);

	boost::asio::io_service ioService;
	boost::asio::ip::udp::socket serverSocket;
	char buffer[512];
	udp::endpoint endpoint;
	boost::asio::deadline_timer spriteUpdateTimer;
	boost::asio::deadline_timer masterServerUpdateTimer;
	boost::asio::deadline_timer removeIdlePlayersTimer;

	boost::thread_group ioThreads;

	unsigned short posUpdate;

	unsigned short maxPlayers;
	unsigned short currentPlayers;

	serverInfoPacket packetServerInfo;
	udp::endpoint masterServerEndpoint;

	static const unsigned short numIOServiceThreads = 8;

	sf::Clock timer;

	class playerInfo
	{
	public:
		playerInfo(){}
		void disconnect(const boost::system::error_code& e);
		std::string name;
		boost::shared_ptr<genericSprite> playerSprite;
		boost::asio::ip::udp::endpoint endpoint;
		bool stillAlive;

	};

	typedef std::map<unsigned short, boost::shared_ptr<playerInfo> > playerContainer;
	playerContainer Players;


};
extern boost::shared_ptr<networkServer> server;

#endif
