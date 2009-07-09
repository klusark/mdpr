#ifndef networkServer_hpp
#define networkServer_hpp

#include <Poco/SharedPtr.h>
#include <map>
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

	int main(const std::vector<std::string>& args);
	
protected:
	//!Initializes the server
	void initialize(Poco::Util::Application& self);

	/*!
	Called when a packet is received
	*/
	void onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification>&);

	/*!
	Called when there is an error
	*/
	void onError(const Poco::AutoPtr<Poco::Net::ErrorNotification>&);

	
	void removeIdlePlayers(Poco::Timer& timer);

	void spriteUpdate(Poco::Timer& timer);
	void masterServerUpdate(Poco::Timer& timer);

	Poco::Timer spriteUpdateTimer;
	Poco::Timer masterServerUpdateTimer;

	void ioServiceThread();

	void disconnect(unsigned short playerID);

	//Poco::TaskManager taskManager;

	unsigned short posUpdate;

	unsigned short maxPlayers;
	unsigned short currentPlayers;

	serverInfoPacket packetServerInfo;

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
	//Poco::Net::SocketAddress socketAddress;
	Poco::Net::DatagramSocket socket;
	char* buffer;


};
extern Poco::SharedPtr<NetworkServer> server;

#endif // #ifndef networkServer_hpp
