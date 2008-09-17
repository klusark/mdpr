#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "SpriteManager.hpp"


class GameManager : public SpriteManager
{
	public:
		GameManager();
		~GameManager();
		void tick();
		bool isActive();
		void activate();
		void startGame();

	private:
		void createLevel();
		void createPlatforms();
		void createRopes();

		bool bActive;
		///used to tell it gameStart should run its code
		bool bStartGame;
		
};
/*! \class GameManager GameManager.hpp "include/GameManager.hpp"
 *  \brief The GameManager class
 *
 * The GameManager class
 */
#endif
