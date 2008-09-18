#include "Player.hpp"

Player::Player(GameManager *sm)
{
	this->sm = sm;
	setCollisionType(player);
}

Player::~Player()
{
}

void Player::update()
{
	Mass::update();
	//get the input
	input();
}

/*! 
 * Gets all the input for the player and acts on it
 */
void Player::input()
{
}
