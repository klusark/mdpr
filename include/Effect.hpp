#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <string>
#include <map>

#include "Sprite.hpp"

class GameManager;

class Effect : public Sprite
{
	public:
		Effect(GameManager *);
		~Effect();
		void update();
		void animationEnd();
		bool isInUse();
		void startEffect(std::string name);
	private:
		std::map<std::string, Animation*> animations;
		bool bInUse;
		GameManager *gm;
};

/*! \class Effect Effect.hpp "include/Effect.hpp"
 *  \brief The Effect class
 *
 * Shows all the diffrent effects
 */

#endif
