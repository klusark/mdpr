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

	private:
		///pixels per second to move down
		static const int gravity = 7;
		///max pixels per second down
		static const int terminalVelocity = 240;
		///the game manager
		GameManager *gm;
		
};
/** \class Mass Mass.hpp "include/Mass.hpp"
 *  \brief The Mass class
 *
 * handles moving any sprites with mass down with gravity
 */
#endif
