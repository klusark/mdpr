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
		/// Checks for collision with a platform
		void checkPlatformCollision();
	private:
		GameManager *gm;
};
/*! \class Mass Mass.hpp "include/Mass.hpp"
 *  \brief The Mass class
 *
 * The Mass class
 */
#endif
