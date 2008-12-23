#ifndef networkClient_hpp
#define networkClient_hpp

#include <boost/asio.hpp>
#include <ClanLib/core.h>
#include <ClanLib/network.h>

class spriteManager;

class Network::Client
{
public:
	Client();
	~Client();
	bool runClient();
protected:
	boost::asio::io_service ioService;
	void onDisconnect(CL_NetComputer &computer);
	void onReciveSprite(CL_NetPacket &packet, CL_NetComputer &computer);

	void onReciveSpriteUpdatePos(CL_NetPacket &packet, CL_NetComputer &computer);
	void onReciveSpriteUpdateAccel(CL_NetPacket &packet, CL_NetComputer &computer);
	void onReciveSpriteUpdateVelocity(CL_NetPacket &packet, CL_NetComputer &computer);

	boost::shared_ptr<CL_NetSession> netsession;
	CL_Slot slotDisconnect, slotReciveSprite, slotReciveSpriteUpdatePos, slotReciveSpriteUpdateVelocity, slotReciveSpriteUpdateAccel;

};

#endif
