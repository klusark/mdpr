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
	updateLevel();
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
	for (short i = 0; i<3; ++i){
		bubbles[i] = new Bubble;
	}
	createLevel();
}

void GameManager::createLevel()
{
	createPlatforms();
	createRopes();
	createMallow();
}

void GameManager::createPlatforms()
{
}

void GameManager::createRopes()
{
}

void GameManager::createMallow()
{
}

/**
* Updates the ropes, platforms, mallow and emitters
*/
void GameManager::updateLevel()
{
}
