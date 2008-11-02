#ifndef MASS_HPP
#define MASS_HPP

#include "Sprite.hpp"

class GameManager;

class Mass : public Sprite
{
	public:
		Mass(GameManager *);
		~Mass();
		virtual void update();
		void applyGravity();
		void checkPlatformCollision();
		virtual void animationEnd();

	protected:
		///true when the sprite is on the ground false when not
		bool isOnGround;
		bool isOverRect(SDL_Rect rect);
		bool isUnderRect(SDL_Rect rect);
		bool isVerticalOfRect(SDL_Rect rect);
		bool isOverBottomOfRect(SDL_Rect rect);
		bool isUnderTopOfRect(SDL_Rect rect);
		bool isUnderBottomOfRect(SDL_Rect rect);
		bool isOverTopOfRect(SDL_Rect rect);
		bool doNotCollideWithPlatform;

		/// is the player not in a controlled fall
		bool isUnstable, unstableRoll;
		
	private:
		///pixels per second to move down
		static const int gravity = 420;
		///max pixels per second down
		static const int terminalVelocity = 240;

		Uint32 lastTimeGrav;

		///the game manager
		GameManager *gm;
		
};
/** \class Mass Mass.hpp "include/Mass.hpp"
 *  \brief The Mass class
 *
 * handles moving any sprites with mass down with gravity
 */
#endif
