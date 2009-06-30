#ifndef networkServer_hpp
#define networkServer_hpp

//#include <boost/asio.hpp>
#include <Poco/SharedPtr.h>
#include <map>
//#include <boost/thread.hpp>
#include <SFML/System/Clock.hpp>

#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/AutoPtr.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Util/TimerTask.h>
#include <Poco/TaskManager.h>
#include <Poco/Util/TimerTaskAdapter.h>
#include <Poco/Util/TimerTask.h>
#include <Poco/Timer.h>


#include "network/packets.hpp"

//using boost::asio::ip::udp;

class genericSprite;
class spriteManager;

//!The server
/*!
A self contained server in a class.
*/
class NetworkServer : public Poco::Util::ServerApplication
{
public:
	//!The constructor
	/*!
	Constructs the server and sets up the async operations.
	*/
	NetworkServer();

	//!The deconstructor
	/*!
	Destroys the server.
	*/
	~NetworkServer();

	/*!
	Waits untill the server is ready to shut down
	*/
	void runServer();

	int main(const std::vector<std::string>& args);
	
protected:
	void initialize(Poco::Util::Application& self);
	/*!
	Called when  a packet is received
	\param error if there is an error, this contains the message.
	\param bytesReceived number of bytes received.
	*/
	void onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf);

	/*!
	Handles async sending of packets
	\param error if there is an error, this contains the message.
	\param bytesSent number of bytes sent.
	*/
	/*void handleSendTo(const boost::system::error_code& error, size_t bytesSent);

	void onSpriteUpdate(const boost::system::error_code& error);

	void updateMasterServer(const boost::system::error_code& error);

	void removeIdlePlayers(const boost::system::error_code& error);
*/
	void onSpriteUpdate(Poco::Timer& timer);
	Poco::Timer spriteUpdateTimer;

	void ioServiceThread();

	void disconnect(unsigned short playerID);

	/*boost::asio::io_service ioService;
	boost::asio::ip::udp::socket serverSocket;
	char buffer[512];
	udp::endpoint endpoint;
	boost::asio::deadline_timer spriteUpdateTimer;
	boost::asio::deadline_timer masterServerUpdateTimer;
	boost::asio::deadline_timer removeIdlePlayersTimer;

	boost::thread_group ioThreads;*/

	Poco::TaskManager taskManager;

	unsigned short posUpdate;

	unsigned short maxPlayers;
	unsigned short currentPlayers;

	serverInfoPacket packetServerInfo;
	//udp::endpoint masterServerEndpoint;

	static const unsigned short numIOServiceThreads = 8;

	sf::Clock timer;

	class playerInfo
	{
	public:
		playerInfo(){}
//		void disconnect(const boost::system::error_code& e);
		std::string name;
		Poco::SharedPtr<genericSprite> playerSprite;
		Poco::Net::SocketAddress address;
		bool stillAlive;

	};

	typedef std::map<unsigned short, Poco::SharedPtr<playerInfo> > playerContainer;
	playerContainer Players;

	enum
	{
		BUFFER_SIZE = 256
	};
	Poco::Net::SocketAddress masterServerAddress;
	Poco::Net::SocketAddress socketAddress;
	Poco::Net::DatagramSocket socket;
	char* buffer;


};
extern Poco::SharedPtr<NetworkServer> server;

#endif
