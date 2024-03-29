#ifndef powerUpManager_hpp
#define powerUpManager_hpp

#include <string>
#include <vector>
#include <Poco/SharedPtr.h>

class RegisterPowerup
{
public:
	RegisterPowerup(std::string name);
};

class PowerUpManager
{
public:
	PowerUpManager();
	~PowerUpManager();
	std::string selectRandom();
	typedef std::vector<std::string> powerUpListContainer;
	powerUpListContainer powerUpList;
	
};

extern PowerUpManager *PUManage;

#endif // #ifndef powerUpManager_hpp
