#include "GameManager.hpp"

GameManager::GameManager(SDL_Surface *screen) : SpriteManager(screen)
{
	bActive = false;
	bStartGame = true;
	this->screen = screen;
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

/**
* Calls the functions that create the level
*/
void GameManager::createLevel()
{
	createPlatforms();
	createRopes();
	createMallow();
}

/**
* Creates the platforms
*/
void GameManager::createPlatforms()
{
}

/**
* Creates the ropes
*/
void GameManager::createRopes()
{
}

/**
* Creates the Marshmallow at the bottom of the screen
*/
void GameManager::createMallow()
{
}

/**
* Updates the ropes, platforms, mallow and emitters
*/
void GameManager::updateLevel()
{
}
