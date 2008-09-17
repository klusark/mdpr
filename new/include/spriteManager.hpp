#ifndef SPRITEANAGER_HPP
#define SPRITEANAGER_HPP

#include "Player.hpp"

class SpriteManager
{
	public:
		SpriteManager();
		~SpriteManager();
		void tick();
	protected:
		Player *player1;
		Player *player2;
};
/*! \class SpriteManager SpriteManager.hpp "include/SpriteManager.hpp"
 *  \brief The SpriteManager class
 *
 * The SpriteManager class
 */
#endif
