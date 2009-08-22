#ifndef PlayerConnection_hpp
#define PlayerConnection_hpp

#include <Poco/Net/DatagramSocket.h>
#include <Poco/Thread.h>
#include <Poco/Net/SocketReactor.h>
#include <Poco/SharedPtr.h>

class GenericSprite;

//Class for each players connection to the server
class PlayerConnection
{
public:
	PlayerConnection(Poco::Net::SocketAddress &ClientAddress, std::string name, bool noSpriteUpdates, GenericSprite* sprite);
	~PlayerConnection();

	Poco::Net::SocketAddress& GetSocketAddress() const {return ClientAddress;};
	bool GetNoSpriteUpdates() const {return noSpriteUpdates;};
	GenericSprite* GetSprite() const {return playerSprite;};
	std::string GetName() const {return name;};
	bool IsAlive() const {return stillAlive;};
	void SetAlive(bool alive) {stillAlive = alive;};


private:
	Poco::Net::DatagramSocket socket;
	Poco::Thread ReactorThread;
	Poco::Net::SocketReactor Reactor;
	std::string name;
	bool noSpriteUpdates, stillAlive;
	GenericSprite* playerSprite;
	Poco::Net::SocketAddress& ClientAddress;
};


#endif // #ifndef PlayerConnection_hpp
