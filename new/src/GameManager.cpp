#include "GameManager.hpp"

GameManager::GameManager()
{
	bActive = false;
	bStartGame = true;
}

GameManager::~GameManager()
{
}

void GameManager::tick()
{
	if (bStartGame)
		startGame();
		bStartGame = false;
	SpriteManager::tick();
}

bool GameManager::isActive()
{
	return bActive;
}

void GameManager::activate()
{
	bActive = true;
}

void GameManager::startGame()
{
	player1 = new Player(1);
	player2 = new Player(2);
	createLevel();
}

void GameManager::createLevel()
{
	createPlatforms();
	createRopes();
}

void GameManager::createPlatforms()
{
}

void GameManager::createRopes()
{
}
