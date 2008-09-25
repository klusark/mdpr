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
		void animationEnd();

	private:
		void actOnInput();
		void input();
		bool isTouchingRope();
		///1 or 2 depending on what player it is.
		short playerNum;
		//copy of the game manager
		GameManager *gm;
		///the run animation
		Animation *runAnimation,
			/// the standing animation
			*standAnimation,
			/// the rolling animation
			*rollAnimation,
			/// the animation that starts when the player presses the crouch key
			*crouchDownAnimation,
			/// the blackflip animation
			*jumpUpAnimation,
			/// the animation when the crouch key is held
			*crouchedAnimation,
			/// the animation when the crouch key is let go of
			*crouchUpAnimation;
		/// the up key
		Uint8 keyUp,
			/// the down key
			keyDown,
			/// the right key
			keyRight,
			/// the left key
			keyLeft;
		/// the last state of the keys
		Uint8 *lastKeystate;

		bool isRunning,
			isRolling,
			isCrouchingDown,
			isJumpingUp,
			isCrouched,
			isCrouchingUp,
			isJumpingForward,
			isJumpingUpStart;
		/// the speed in the x the palyer goes at when walking
		static const int walkSpeed		= 32;
		/// the speed in the x the palyer goes at when rolling
		static const int rollSpeed		= 40;
		/// the speed in the y the player goes when jumping up
		static const int jumpUpSpeed	= -100;
};

/*! \class Player player.hpp "include/player.hpp"
 *  \brief The Player class
 *
 * The Player class
 */

#endif
