#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <stdio.h>
#include "SDL/SDL.h"
#include "SpriteManager.hpp"
#include "WeaponManager.hpp"
#include <map>
#include <string>
#include <queue>


class GameManager : public SpriteManager
{
	public:
		GameManager(SDL_Surface *screen, int width, int height);
		~GameManager();
		void tick();
		bool isActive();
		void activate();
		void startGame();
		void addToImageQueue(SDL_Surface *, SDL_Rect, short layer);
		void drawImageQueue();
		void clearRect(SDL_Rect);
		void newEffect(std::string name);
		SDL_Rect makeRect(Uint16 h, Uint16 w, Sint16 x, Sint16 y);
		std::map<std::string, SDL_Surface *> images;
		std::map<std::string, SDL_Surface *> flippedImages;
		SDL_Surface *screen;
		struct Queue
		{
			SDL_Surface *image;
			SDL_Rect rect;
		};
		std::queue<Queue> imageQueue[4];

		int width, height;
		static const int numPlatforms = 70;
		static const int numRopes = 2;
		SDL_Rect platforms[numPlatforms], ropes[numRopes];

		SDL_Surface *flipImage(SDL_Surface *image);
		void putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
		Uint32 getPixel(SDL_Surface *surface, int x, int y);
	private:
		void createLevel();
		void createPlatforms();
		void createRopes();
		void createMallow();
		void updateLevel();
		void loadImages();
		void throttleFPS(short FPS);

		bool bActive;
		///used to tell it gameStart should run its code
		bool bStartGame;

		Uint32 currentTicks, lastTicks;
		Uint16 test;
		
		

};
/*! \class GameManager GameManager.hpp "include/GameManager.hpp"
 *  \brief The GameManager class
 *
 * Manages everything in game
 */
#endif
