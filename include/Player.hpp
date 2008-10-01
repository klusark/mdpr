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
		void collideWithRopeEnds();
		bool isTouchingRope();

		///1 or 2 depending on what player it is.
		short playerNum;
		//copy of the game manager
		GameManager *gm;
		///the run animation
		Animation *runAnimation,
			/// the idleing animation
			*idleAnimation,
			/// the rolling animation
			*rollAnimation,
			/// the animation that starts when the player presses the crouch key
			*crouchDownAnimation,
			/// the blackflip animation
			*jumpUpAnimation,
			/// the animation when the crouch key is held
			*crouchedAnimation,
			/// the animation when the crouch key is let go of
			*crouchUpAnimation,
			///	the animation when the player is on the rope;
			*climbAnimation,
			/// the animation when the player jumps forward
			*jumpForwardAnimation,
			*fallUnstableAnimation;

		/// the up key
		SDLKey keyUp,
			/// the down key
			keyDown,
			/// the right key
			keyRight,
			/// the left key
			keyLeft;
		/// the last state of the keys
		Uint8 *lastKeystate;
		
		/// is the player currently running
		bool isRunning,
			/// is the player currently rolling
			isRolling,
			/// is the player currently starting to crouch
			isCrouchingDown,
			/// is the player currently jumping up
			isJumpingUp,
			/// is the player currently fully crouched
			isCrouched,
			/// is the player currently ending crouching
			isCrouchingUp,
			/// is the player currently climbing the rope
			isClimbingRope,
			/// is the player currently starting to jump up
			isJumpingUpStart,
			/// is the player currently jumpping forward
			isJumppingForward,
			isJumppingForwardStart,
			isFallingUnstable,
			noFlip;


		/// the speed in the x the palyer goes at when walking
		static const int walkSpeed			=  120;
		/// the speed in the x the palyer goes at when rolling
		static const int rollSpeed			=  120;
		/// the speed in the y the player goes when jumping up
		static const int jumpUpSpeed		= -150;
		/// the speed in the y the player goes when moving on the rope
		static const int ropeSpeed			=  120;
		static const int jumpForwardYSpeed	= -150;
		static const int jumpForwardXSpeed	=  120;
};

/** \class Player player.hpp "include/player.hpp"
 *  \brief The Player class
 *
 * The Player class
 */

#endif
