#include "SDL.h"
#include <string>
#include <map>
#include "SDL_image.h"

#include "Player.hpp"
#include "Bubble.hpp"
#include "Effect.hpp"
#include "GameManager.hpp"

GameManager::GameManager(SDL_Surface *screen) : SpriteManager(screen)
{
	bActive = false;
	bStartGame = true;
	this->screen = screen;
	loadImages();
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
	player1 = new Player(this);
	player2 = new Player(this);
	for (short i = 0; i<3; ++i){
		bubbles[i] = new Bubble(this);
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

void GameManager::addToImageQueue()
{
}

void GameManager::drawImageQueue()
{
}

void GameManager::clearRect(SDL_Rect rect)
{
	SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 0, 0));
}

void GameManager::loadImages()
{
	std::string imageList[] = {"stand", "run0"};
	SDL_RWops *rwop;
	char files[32];
	for (short i = 0; i < 2; ++i){
		sprintf(files, "data/main/%s.png", imageList[i]);
		rwop = SDL_RWFromFile(files, "rb");
		images[imageList[i]] = IMG_LoadPNG_RW(rwop);
	}
}
