#ifndef networkServer_hpp
#define networkServer_hpp
#if _MSC_VER > 1000
#pragma once
#endif

#include "network.hpp"
class Network::Server
{
public:
	bool runServer();
protected:
	void onConnect(CL_NetComputer &computer);
	void onDisconnect(CL_NetComputer &computer);
	void onReciveConnect(CL_NetPacket &packet, CL_NetComputer &computer);
	CL_NetSession *netsession;
	CL_Slot slotReciveConnect;
	CL_Slot slotConnect;
	CL_Slot slotDisconnect;

};

#endif
