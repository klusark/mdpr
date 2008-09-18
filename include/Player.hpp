#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "GameManager.hpp"
#include "Mass.hpp"

class GameManager;

class Player : public Mass
{
	public:
		Player(GameManager *sm);
		~Player();
		void update();
		void input();
	private:
		///1 or 2 depending on what player it is.
		short playerNum;

		GameManager *sm;
};

/*! \class Player player.hpp "include/player.hpp"
 *  \brief The Player class
 *
 * The Player class
 */

#endif
