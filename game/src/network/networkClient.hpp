#ifndef networkClient_hpp
#define networkClient_hpp

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <SFML/Window/Event.hpp>

#include <SFML/System/Clock.hpp>

#include "packets.hpp"

class ClientSpriteManager;
using boost::asio::ip::udp;

class networkClient
{
public:
	networkClient();
	~networkClient();
	bool connect();
	void sendKeyPress(sf::Key::Code key, bool down);
	bool connected;

	//typedef std::vector<fullServerEntry> fullServerContainter;
	//typedef std::vector<fullServerEntry *> fullServerContainter2;
	std::vector<fullServerEntry> serverList;

	connectionState currentState;
protected:
	boost::asio::io_service ioService;
	udp::socket socket;
	bool inGame;
	

	sf::Clock timer;

	udp::endpoint receiverEndpoint;
	udp::endpoint masterServerEndpoint;

	boost::thread_group serverListUpdateThreads;
	boost::thread_group ioServiceThreadPool;

	void onReceivePacket(const boost::system::error_code& error, size_t bytesReceived);
	void handleSendTo();
	void serverListUpdateThread(int i);
	void ioServiceThread();

	static const unsigned short numServerUpdateThreads = 1;
	
	static const unsigned short numIOServiceThreads = 5;

	char buffer[256];


	std::vector<fullServerEntry *> serversToUpdate[numServerUpdateThreads];

	unsigned int totalBytesRecived, bytesInLastFive;

};

#endif // #ifndef networkClient_hpp
