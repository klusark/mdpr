#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Mass.hpp"

class Player : public Mass
{
	public:
		Player(short);
		~Player();
		void update();
		void input();
};

/*! \class Player player.hpp "include/player.hpp"
 *  \brief The Player class
 *
 * The Player class
 */

#endif
