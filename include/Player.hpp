#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Mass.hpp"

class GameManager;

class Player : public Mass
{
	public:
		Player(GameManager *, short);
		~Player();
		void update();
		void input();
	private:
		///1 or 2 depending on what player it is.
		short playerNum;

		GameManager *gm;
};

/*! \class Player player.hpp "include/player.hpp"
 *  \brief The Player class
 *
 * The Player class
 */

#endif
