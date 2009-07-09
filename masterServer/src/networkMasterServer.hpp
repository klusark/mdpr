#ifndef networkMasterServer_hpp
#define networkMasterServer_hpp

#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/Util/ServerApplication.h>

#include <vector>
#include "network/packets.hpp"

//!The master server class
class NetworkMasterServer : public Poco::Util::ServerApplication
{
public:
	//!constructor
	NetworkMasterServer();

	//!deconstructor
	~NetworkMasterServer();

	//!Equivilent to a global main.
	int main(const std::vector<std::string>& args);
protected:
	//!Called when a packet is received
	void onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf);

	//!initializes the application
	void initialize(Poco::Util::Application& self);

	typedef std::vector<serverEntry> serverListContainer;
	serverListContainer serverList;

	enum
	{
		//!The size of the buffer
		BUFFER_SIZE = 256
	};
	//!the socket used for all communication
	Poco::Net::DatagramSocket socket;

	//!the buffer used for reciveing information
	char* buffer;

};

#endif // #ifndef networkMasterServer_hpp
