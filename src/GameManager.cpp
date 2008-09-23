#include "SDL.h"
#include <string>
#include <map>
#include <vector>
#include "SDL_image.h"

#include "Player.hpp"
#include "Bubble.hpp"
#include "Effect.hpp"
#include "GameManager.hpp"

/**
 * consturcts the gamemanager
 */
GameManager::GameManager(SDL_Surface *screen, int width, int height) : SpriteManager(screen)
{
	this->height = height;
	this->width = width;
	bActive = false;
	bStartGame = true;
	this->screen = screen;
	loadImages();
	queuedImages = 0;
}

GameManager::~GameManager()
{

	std::map<std::string, SDL_Surface *>::iterator iter;
    for( iter = images.begin(); iter != images.end(); ++iter ) {
		SDL_FreeSurface(iter->second);

    }
	images.clear();
	delete player1;
	delete player2;
}

void GameManager::tick()
{
	if (bStartGame){
		startGame();
		bStartGame = false;
	}
	updateLevel();
	SpriteManager::tick();
	
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
	short yTemp = 0, xTemp = 0;
	short i, h = 8, w = 14;
	
	for (i = 0; i <= 15; ++i){
		if (i == 0){
			//bottom left
			yTemp = 168;
			xTemp = 25;
		}else if(i == 4){
			//bottom right
			xTemp = 233;
		}else if(i == 8){
			//top left
			yTemp = 40;
			xTemp = 49;
		}else if(i == 12){
			//top right
			xTemp = 209;
		}
		platforms[i] = makeRect(h, w, xTemp, yTemp);
		xTemp += 16;
	}
	
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
	for (short i = 0; i < 16; ++i){
		addToImageQueue(images["platform"], platforms[i]);
	}
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
	SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));
}

void GameManager::loadImages()
{
	std::string imageList[] = {
		"stand",
		"run0", "run1", "run2", "run3",
		"roll0", "roll1", "roll2", "roll3",
		"bubble0", "bubble1", "bubble2",
		"platform"
	};
	SDL_RWops *rwop;
	
	for (short i = 0; i < 13; ++i){
		std::string file;
		file += "data/main/";
		file += imageList[i];
		file += ".png";
		rwop = SDL_RWFromFile(file.c_str(), "rb");
		images[imageList[i]] = IMG_LoadPNG_RW(rwop);
		if (!images[imageList[i]])
			printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
	SDL_FreeRW(rwop);
}

SDL_Rect GameManager::makeRect(Uint16 h, Uint16 w, Uint16 x, Uint16 y)
{
	SDL_Rect rect;
	rect.h = h;
	rect.w = w;
	rect.x = x;
	rect.y = y;
	return rect;
}
