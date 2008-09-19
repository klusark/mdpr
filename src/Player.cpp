#include "GameManager.hpp"
#include "Player.hpp"

Player::Player(GameManager *gm, short playerNum) : Mass(gm)
{
	this->gm = gm;
	this->playerNum = playerNum;
	setCollisionType(player);
	rect.x = 50;
	rect.y = 50;
	rect.h = 24;
	rect.w = 24;
	image = gm->images["stand"];
}

Player::~Player()
{
}

void Player::update()
{
	Mass::update();
	//SDL_BlitSurface(gm->images["stand"], 0, gm->screen, &rect);
	//get the input
	input();
}

/*! 
 * Gets all the input for the player and acts on it
 */
void Player::input()
{
}
