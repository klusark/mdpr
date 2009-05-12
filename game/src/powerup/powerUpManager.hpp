#ifndef powerUpManager_hpp
#define powerUpManager_hpp

#include <string>
#include <vector>

class RegisterPowerup
{
public:
	RegisterPowerup(std::string name);
};

class PowerUpManager
{
public:
	PowerUpManager();
	std::string selectRandom();
	typedef std::vector<std::string> powerUpListContainer;
	static powerUpListContainer powerUpList;
};

#endif