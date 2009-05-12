#include "powerUpManager.hpp"

PowerUpManager::powerUpListContainer PowerUpManager::powerUpList;

RegisterPowerup::RegisterPowerup(std::string name)
{
	PowerUpManager::powerUpList.push_back(name);
}

PowerUpManager::PowerUpManager()
{
}

std::string PowerUpManager::selectRandom()
{
	return "gun";
}