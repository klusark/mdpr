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

	//!The main function for the server called by the Poco::Util::Application stuff
	/*!
	@param args the arguments from the command line
	*/
	int main(const std::vector<std::string>& args);
	
protected:
	//!Initializes the server
	void initialize(Poco::Util::Application& self);

	//!Called when a packet is received
	void onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification>&);

	//!Called when there is an error
	void onError(const Poco::AutoPtr<Poco::Net::ErrorNotification>&);

	//!Removes any player that has not sent a packet
	/*!
	@param timer a copy of the timer
	*/
	void removeIdlePlayers(Poco::Timer& timer);

	//!Updates the sprites and sends them to the clients
	/*!
	@param timer a copy of the timer
	*/
	void spriteUpdate(Poco::Timer& timer);

	//!Updates the master server
	/*!
	@param timer a copy of the timer
	*/
	void masterServerUpdate(Poco::Timer& timer);

	//!Disconnects a player
	/*!
	@param playerID the player to disconnect
	*/
	void disconnect(unsigned short playerID);

	//!the timer for sprite updates
	Poco::Timer spriteUpdateTimer;

	//!the timer for master server updates
	Poco::Timer masterServerUpdateTimer;

	//!the timer for master server updates
	Poco::Timer removeIdlePlayersTimer;

	unsigned short posUpdate;

	//!The max amount of player
	unsigned short maxPlayers;

	//!The current number of players
	unsigned short currentPlayers;

	serverInfoPacket packetServerInfo;

	sf::Clock timer;

	class playerInfo
	{
	public:
		playerInfo(){}
		std::string name;
		Poco::SharedPtr<genericSprite> playerSprite;
		Poco::Net::SocketAddress address;
		bool stillAlive, noSpriteUpdates;
	};

	typedef std::map<unsigned short, Poco::SharedPtr<playerInfo> > playerContainer;
	playerContainer Players;

	enum
	{
		BUFFER_SIZE = 256
	};
	Poco::Net::SocketAddress masterServerAddress;
	Poco::Net::DatagramSocket socket;
	char* buffer;

};

extern Poco::SharedPtr<NetworkServer> server;

#endif // #ifndef networkServer_hpp
