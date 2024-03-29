#ifndef networkClient_hpp
#define networkClient_hpp

#include <SFML/Window/Event.hpp>

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

#include "packets.hpp"

class ClientSpriteManager;

class NetworkClient
{
public:
	NetworkClient();
	~NetworkClient();
	void connectToServer(std::string ip, std::string port, bool noSpriteUpdate, std::string playerName);
	void connectToServer(serverEntry entry, bool noSpriteUpdate, std::string playerName);

	void connectToMaster();

	void sendKeyPress(sf::Key::Code key, bool down);

	bool isInGame() const {return inGame;};

	bool connected;

	//typedef std::vector<fullServerEntry> fullServerContainter;
	//typedef std::vector<fullServerEntry *> fullServerContainter2;
	std::vector<fullServerEntry> serverList;

	connectionState currentState;
	Poco::Net::SocketAddress serverAddress;
	Poco::Net::DatagramSocket socket;
protected:
	Poco::Thread thread;
	Poco::Net::SocketReactor reactor;
	bool inGame;


	sf::Clock timer;

	void onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf);
	void handleSendTo();
	void serverListUpdateThread(Poco::Timer&);

	static const unsigned short numServerUpdateThreads = 1;

	static const unsigned short numIOServiceThreads = 5;

	Poco::Timer serverListUpdateTimer;

	char* buffer;

	enum
	{
		BUFFER_SIZE = 256
	};


	std::vector<fullServerEntry> serversToUpdate[numServerUpdateThreads];

	unsigned int totalBytesRecived, bytesInLastFive;

};

#endif // #ifndef networkClient_hpp
