#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "SpriteManager.hpp"
#include <map>
#include <string>
#include <vector>

class SpriteManager;
struct SDL_Surface;

class GameManager : public SpriteManager
{
	public:
		GameManager(SDL_Surface *screen, int width, int height);
		~GameManager();
		void tick();
		bool isActive();
		void activate();
		void startGame();
		void addToImageQueue(SDL_Surface *, SDL_Rect);
		void drawImageQueue();
		void clearRect(SDL_Rect);
		SDL_Rect makeRect(Uint16 h, Uint16 w, Uint16 x, Uint16 y);
		std::map<std::string, SDL_Surface *> images;
		SDL_Surface *screen;
		struct Queue
		{
			SDL_Surface *image;
			SDL_Rect rect;
		};
		
		Queue imageQueue[32];
		short queuedImages;
		int width, height;
		SDL_Rect platforms[16];
	private:
		void createLevel();
		void createPlatforms();
		void createRopes();
		void createMallow();
		void updateLevel();
		void loadImages();

		bool bActive;
		///used to tell it gameStart should run its code
		bool bStartGame;
		
		

};
/*! \class GameManager GameManager.hpp "include/GameManager.hpp"
 *  \brief The GameManager class
 *
 * Manages everything in game
 */
#endif
