#ifndef MASS_HPP
#define MASS_HPP

#include "Sprite.hpp"

class GameManager;

class Mass : public Sprite
{
	public:
		Mass(GameManager *);
		~Mass();
		void update();
		void applyGravity();
		void checkPlatformCollision();
	protected:
		bool isOnGround;
	private:
		bool isOverRect(SDL_Rect rect);
		bool isUnderRect(SDL_Rect rect);
		GameManager *gm;
		/// the last time the y was moved
		
};
/*! \class Mass Mass.hpp "include/Mass.hpp"
 *  \brief The Mass class
 *
 * The Mass class
 */
#endif
