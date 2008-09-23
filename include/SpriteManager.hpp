#ifndef SPRITEANAGER_HPP
#define SPRITEANAGER_HPP

#include "SDL/SDL.h"
#include <vector>


class Player;
class Bubble;
class Effect;

class SpriteManager
{
	public:
		SpriteManager(SDL_Surface *);
		~SpriteManager();
		void tick();
		void checkCollions();

	protected:
		Player *player1;
		Player *player2;
		Bubble *bubbles[3];
		std::vector<Effect*> effects;

	private:
		SDL_Surface *screen;
};
/*! \class SpriteManager SpriteManager.hpp "include/SpriteManager.hpp"
 *  \brief The SpriteManager class
 *
 * The SpriteManager class
 */
#endif
