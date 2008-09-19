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
	//imageQueue.resize(3);
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
	Queue tempQueue;
	tempQueue.image = image;
	tempQueue.rect = rect;
	imageQueue.push_back(&tempQueue);
	
}

void GameManager::drawImageQueue()
{


	for (std::vector<Queue*>::iterator Iter = this->imageQueue.begin(); Iter != this->imageQueue.end(); ++Iter){
		//SDL_BlitSurface((*Iter)->image, 0, screen, &(*Iter)->rect);
	}
	this->imageQueue.clear();
	//imageQueue
	
}

void GameManager::clearRect(SDL_Rect rect)
{
	SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 0, 0));
}

void GameManager::loadImages()
{
	std::string imageList[] = {"stand", "run0", "run1"};
	SDL_RWops *rwop;
	std::string file;
	for (short i = 0; i < 2; ++i){
		
		file += "data/main/";
		file += imageList[i];
		file += ".png";
		//static_cast<char>(file);
		//sprintf(files, "data/main/%s.png", imageList[i]);
		rwop = SDL_RWFromFile(file.c_str(), "rb");
		images[imageList[i]] = IMG_LoadPNG_RW(rwop);
	}
}
