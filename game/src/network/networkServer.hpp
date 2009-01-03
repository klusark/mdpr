#ifndef networkServer_hpp
#define networkServer_hpp

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

	/*void onDisconnect(CL_NetComputer &computer);
	void onReciveConnect(CL_NetPacket &packet, CL_NetComputer &computer);
	

	boost::shared_ptr<CL_NetSession> netsession;
	CL_Slot slotReciveConnect;
	CL_Slot slotConnect;
	CL_Slot slotDisconnect;
	CL_Slot slotSpriteUpdate;

	CL_Timer timerSpriteUpdate;*/

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
