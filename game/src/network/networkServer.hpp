#ifndef networkServer_hpp
#define networkServer_hpp

#include <boost/shared_ptr.hpp>
#include <map>

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
	void onConnect(CL_NetComputer &computer);
	void onDisconnect(CL_NetComputer &computer);
	void onReciveConnect(CL_NetPacket &packet, CL_NetComputer &computer);
	void onSpriteUpdate();

	boost::shared_ptr<CL_NetSession> netsession;
	CL_Slot slotReciveConnect;
	CL_Slot slotConnect;
	CL_Slot slotDisconnect;
	CL_Slot slotSpriteUpdate;

	CL_Timer timerSpriteUpdate;

	unsigned short posUpdate;

	boost::shared_ptr<spriteManager> sprite;

	unsigned short maxPlayers;
	unsigned short currentPlayers;

	struct playerInfo
	{
		std::string name;
		boost::shared_ptr<genericSprite> sprite;

	};

	typedef std::map<std::string, boost::shared_ptr<playerInfo> > playerContainer;
	playerContainer Players;


};

#endif
