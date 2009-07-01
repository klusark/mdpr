#ifndef networkMasterServer_hpp
#define networkMasterServer_hpp

#include <vector>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/AutoPtr.h>
#include <Poco/Util/ServerApplication.h>

#include "network/packets.hpp"

class NetworkMasterServer : public Poco::Util::ServerApplication
{
public:
	NetworkMasterServer();
	~NetworkMasterServer();
	int main(const std::vector<std::string>& args);
	void stopServer();
protected:

	void onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf);
	void initialize(Poco::Util::Application& self);

	void ioServiceThread();

	typedef std::vector<serverEntry> serverListContainer;
	serverListContainer serverList;

	static const unsigned short numIOServiceThreads = 5;

	enum
	{
		BUFFER_SIZE = 256
	};
	
	Poco::Net::SocketAddress socketAddress;
	Poco::Net::DatagramSocket socket;
	char* buffer;

};

#endif // #ifndef networkMasterServer_hpp
