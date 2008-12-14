#ifndef network_hpp
#define network_hpp

class spriteManager;

class Network
{
public:
	Network(spriteManager *sprite);
	~Network();
	void update();
	class Server;
	class Client;

	
};

#endif