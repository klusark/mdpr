#include "GameManager.hpp"
#include "Mass.hpp"

/**
 * consturcts the mass part of a sprite
 */
Mass::Mass(GameManager *gm) : Sprite(gm)
{
	this->gm = gm;
	isOnGround = false;
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
	double test = (gravity * (SDL_GetTicks() - lastTimeY)/1000.0);
	yVelocity += test;
	if (yVelocity > terminalVelocity){
		yVelocity = terminalVelocity;
	}

}

void Mass::checkPlatformCollision()
{
	isOnGround = false;
	move();
	short smallestDistance = 320;
	rect.y -= static_cast<Sint16>(yMove);
	for (short i = 0; i < 16; ++i){
		if (isOverRect(gm->platforms[i]) && isVerticalOfRect(gm->platforms[i])){
			rect.y += static_cast<Sint16>(yMove);
			if (isUnderRect(gm->platforms[i])){
				if (gm->platforms[i].y < smallestDistance){
					smallestDistance = gm->platforms[i].y;
				}
				//move player to platform
				//rect.y = gm->platforms[i].y - rect.h;
				//isOnGround = true;
				//yVelocity = 0;
				//yMove = 0;

				//return;
			}
			rect.y -= static_cast<Sint16>(yMove);
		}
	}
	if (smallestDistance != 320){
		rect.y = smallestDistance - rect.h;
		isOnGround = true;
		yVelocity = 0;
		yMove = 0;
		return;
	}
	rect.y += static_cast<Sint16>(yMove);
}

bool Mass::isOverRect(SDL_Rect tempRect)
{
	if (rect.y + rect.h <= tempRect.y){
		return true;
	}
	return false;
}

bool Mass::isUnderRect(SDL_Rect tempRect)
{

	if (tempRect.y <= rect.y + rect.h){
		return true;
	}

	return false;
}

bool Mass::isVerticalOfRect(SDL_Rect tempRect)
{
	if (tempRect.x + tempRect.w > rect.x &&tempRect.x < rect.x + rect.w){
		return true;
	}
	return false;
}
void Mass::animationEnd()
{
}
