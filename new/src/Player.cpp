#include <stdio.h>
#include "Player.hpp"

Player::Player(short playerNum)
{
	this->playerNum = playerNum;
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
