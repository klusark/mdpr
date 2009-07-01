#include <Poco/Random.h>
#include "powerUpManager.hpp"

PowerUpManager *PUManage;
static bool made = false;

RegisterPowerup::RegisterPowerup(std::string name)
{
	if (!made){
		PUManage = new PowerUpManager;
		made = true;
	}
	PUManage->powerUpList.push_back(name);
}

PowerUpManager::PowerUpManager()
{

}

PowerUpManager::~PowerUpManager()
{
}

std::string PowerUpManager::selectRandom()
{
	Poco::Random random;
	random.seed();
	
	unsigned int rand = random.next(6);;
	return powerUpList[rand];
}