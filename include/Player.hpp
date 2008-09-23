#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Mass.hpp"

class GameManager;

class Player : public Mass
{
	public:
		Player(GameManager *, short);
		~Player();
		void update();
		void input();
	private:
		void actOnInput();
		///1 or 2 depending on what player it is.
		short playerNum;

		GameManager *gm;

		Animation *runAnimation, *standAnimation, *rollAnimation, *crouchAnimation, *jumpUpAnimation;
		Uint8 keyUp, keyDown, keyRight, keyLeft;
		Uint8 *lastKeystate;
		bool isRunning, isRolling, isCrouching, isJumpingUp;
		static const int walkspeed = 32;
};

/*! \class Player player.hpp "include/player.hpp"
 *  \brief The Player class
 *
 * The Player class
 */

#endif
