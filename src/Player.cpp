#include "Player.hpp"

Player::Player(GameManager *gm) : Mass(gm)
{
	this->gm = gm;
	setCollisionType(player);
	rect.x = 50;
	rect.y = 50;
	rect.h = 50;
	rect.w = 50;
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
