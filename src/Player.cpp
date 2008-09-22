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

	SDL_Surface *runFrames[] = {gm->images["run0"], gm->images["run1"], gm->images["run2"], gm->images["run3"]};
	runAnimation = makeAnimaion(4, 100, runFrames);

	SDL_Surface *idleFrames[] = {gm->images["stand"]};
	standAnimation = makeAnimaion(1, 100, idleFrames);

	currentAnimation = standAnimation;

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
