#include "SDL.h"
#include <string>
#include <map>
#include <vector>
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
	queuedImages = 0;
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
	drawImageQueue();
	SDL_Flip(screen);
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
	player1 = new Player(this, 1);
	player2 = new Player(this, 2);
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

void GameManager::addToImageQueue(SDL_Surface *image, SDL_Rect rect)
{
	imageQueue[queuedImages].image = image;
	imageQueue[queuedImages].rect = rect;
	++queuedImages;
}

void GameManager::drawImageQueue()
{
	for (short i = 0; i < queuedImages; ++i){
		SDL_BlitSurface(imageQueue[i].image, 0, screen, &imageQueue[i].rect);
	}
	queuedImages = 0;
}

void GameManager::clearRect(SDL_Rect rect)
{
	SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 0, 0));
}

void GameManager::loadImages()
{
	std::string imageList[] = {"stand", "run0", "run1", "bubble0", "bubble1", "bubble2" };
	SDL_RWops *rwop;
	
	for (short i = 0; i < 6; ++i){
		std::string file;
		file += "data/main/";
		file += imageList[i];
		file += ".png";
		rwop = SDL_RWFromFile(file.c_str(), "rb");
		images[imageList[i]] = IMG_LoadPNG_RW(rwop);
		if (!images[imageList[i]])
			printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());

	}
}
