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
		bool isOnGround;
	private:
		bool isOverRect(SDL_Rect rect);
		bool isUnderRect(SDL_Rect rect);
		bool isVerticalOfRect(SDL_Rect rect);
		static const int gravity = 32;
		static const int terminalVelocity = 240;
		GameManager *gm;
		/// the last time the y was moved
		
};
/*! \class Mass Mass.hpp "include/Mass.hpp"
 *  \brief The Mass class
 *
 * The Mass class
 */
#endif
