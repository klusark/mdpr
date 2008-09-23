#include "GameManager.hpp"
#include "Mass.hpp"

/**
 * consturcts the mass part of a sprite
 */
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
	yVelocity = 30;

}

void Mass::checkPlatformCollision()
{
	for (short i = 0; i < 16; ++i){
		if (isOverRect(gm->platforms[i])){
			move();
			if (isUnderRect(gm->platforms[i])){
				//move player to platform
				rect.y = gm->platforms[i].y-rect.h;
			}
		}
	}
}

bool Mass::isOverRect(SDL_Rect tempRect)
{
	if (tempRect.x + tempRect.w > rect.x &&tempRect.x < rect.x + rect.w){
		if (tempRect.y > rect.y + rect.h - 1){
			return true;
		}
	}
	return false;
}

bool Mass::isUnderRect(SDL_Rect tempRect)
{
	if (tempRect.x + tempRect.w > rect.x &&tempRect.x < rect.x + rect.w){
		if (tempRect.y < rect.y + rect.h){
			return true;
		}
	}
	return false;
}