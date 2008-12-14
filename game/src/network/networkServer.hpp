#ifndef networkServer_hpp
#define networkServer_hpp

#include "network.hpp"
#include <map>

class Player;
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

	CL_NetSession *netsession;
	CL_Slot slotReciveConnect;
	CL_Slot slotConnect;
	CL_Slot slotDisconnect;
	CL_Slot slotSpriteUpdate;

	CL_Timer timerSpriteUpdate;

	unsigned short posUpdate;

	spriteManager *sprite;

	unsigned short maxPlayers;
	unsigned short currentPlayers;

	struct playerInfo
	{
		std::string name;
		Player *sprite;

	};

	typedef std::map<std::string, playerInfo *> playerContainer;
	playerContainer Players;


};

#endif
