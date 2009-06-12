#include <boost/random.hpp>
#include <time.h>
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
	boost::mt19937 rng;
	rng.seed((boost::uint32_t)time(0));

	boost::uniform_int<> myRange(0, powerUpList.size()-1);

	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > myRand(rng, myRange);

	int rand = myRand();
	return powerUpList[rand];
}