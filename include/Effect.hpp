#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "Sprite.hpp"

class GameManager;

class Effect : public Sprite
{
	public:
		Effect(GameManager *);
		~Effect();
		void update();
		void animationEnd();
	private:
		GameManager *gm;
};

/*! \class Effect Effect.hpp "include/Effect.hpp"
 *  \brief The Effect class
 *
 * Shows all the diffrent effects
 */

#endif
