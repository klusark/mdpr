#ifndef networkClient_hpp
#define networkClient_hpp


#include "network.hpp"
class Network::Client
{
public:
	bool runClient();
protected:
	void onDisconnect(CL_NetComputer &computer);
	CL_NetSession *netsession;
	CL_Slot slotDisconnect;

};

#endif
