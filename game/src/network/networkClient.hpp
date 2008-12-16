#ifndef networkClient_hpp
#define networkClient_hpp

#include "network.hpp"

class spriteManager;

class Network::Client
{
public:
	Client();
	~Client();
	bool runClient();
protected:
	void onDisconnect(CL_NetComputer &computer);
	void onReciveSprite(CL_NetPacket &packet, CL_NetComputer &computer);

	void onReciveSpriteUpdatePos(CL_NetPacket &packet, CL_NetComputer &computer);
	void onReciveSpriteUpdateAccel(CL_NetPacket &packet, CL_NetComputer &computer);
	void onReciveSpriteUpdateVelocity(CL_NetPacket &packet, CL_NetComputer &computer);

	boost::shared_ptr<CL_NetSession> netsession;
	CL_Slot slotDisconnect, slotReciveSprite, slotReciveSpriteUpdatePos, slotReciveSpriteUpdateVelocity, slotReciveSpriteUpdateAccel;

};

#endif
