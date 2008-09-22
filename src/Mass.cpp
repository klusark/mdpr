#include "Mass.hpp"

Mass::Mass(GameManager *gm) : Sprite(gm)
{
	this->gm = gm;
	lastTimeY = 0;
}

Mass::~Mass()
{
}

void Mass::update()
{
	applyGravity();
	checkPlatformCollision();

	Sprite::update();
	
	
}

void Mass::applyGravity()
{
	
	
	
	double ymove = (10 * (SDL_GetTicks() - lastTimeY)/1000.0);
	if (ymove > 1 || ymove < -1){
		lastTimeY = SDL_GetTicks();
		move(0, static_cast<short>(ymove));
	}
}

void Mass::checkPlatformCollision()
{
}