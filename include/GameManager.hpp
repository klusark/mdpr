#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "SDL.h"

#include "SpriteManager.hpp"

class SpriteManager;

class GameManager : public SpriteManager
{
	public:
		GameManager(SDL_Surface*);
		~GameManager();
		void tick();
		bool isActive();
		void activate();
		void startGame();

	private:
		void createLevel();
		void createPlatforms();
		void createRopes();
		void createMallow();
		void updateLevel();

		bool bActive;
		///used to tell it gameStart should run its code
		bool bStartGame;
		///the main screen for the game
		SDL_Surface *screen;
		
};
/*! \class GameManager GameManager.hpp "include/GameManager.hpp"
 *  \brief The GameManager class
 *
 * Manages everything in game
 */
#endif
