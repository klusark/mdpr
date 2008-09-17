#ifndef SPRITEANAGER_HPP
#define SPRITEANAGER_HPP

#include <vector>

#include "Player.hpp"
#include "Bubble.hpp"
#include "Effect.hpp"

class SpriteManager
{
	public:
		SpriteManager();
		~SpriteManager();
		void tick();
		void checkCollions();
	protected:
		Player *player1;
		Player *player2;
		Bubble *bubbles[3];
		std::vector<Effect*> effects;
};
/*! \class SpriteManager SpriteManager.hpp "include/SpriteManager.hpp"
 *  \brief The SpriteManager class
 *
 * The SpriteManager class
 */
#endif
