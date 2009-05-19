#ifndef networkClient_hpp
#define networkClient_hpp

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <SFML/Window/Event.hpp>

#include "packets.hpp"

class spriteManager;
using boost::asio::ip::udp;

struct fullServerEntry
{
	serverEntry entry;
	unsigned char numPlayers;
	unsigned char maxPlayers;
	std::string serverName;
};

class networkClient
{
public:
	networkClient();
	~networkClient();
	bool connect();
	void sendKeyPress(sf::Key::Code key, bool down);
	bool connected;

	typedef std::vector<fullServerEntry> fullServerContainter;
	typedef std::vector<fullServerEntry *> fullServerContainter2;
	fullServerContainter serverList;

	static const unsigned short numServerUpdateThreads = 1;
	fullServerContainter2 serversToUpdate[numServerUpdateThreads];
protected:
	boost::asio::io_service ioService;
	udp::socket socket;
	bool inGame;
	char buffer[512];
	udp::endpoint receiverEndpoint;
	udp::endpoint masterServerEndpoint;

	boost::thread_group serverListUpdateThreads;
	boost::thread *ioThread;

	void onReceivePacket(const boost::system::error_code& error, size_t bytesReceived);
	void handleSendTo();

	unsigned int totalBytesRecived;

};

#endif //networkClient_hpp
