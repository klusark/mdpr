#include "GameManager.hpp"
#include "Mass.hpp"

/**
 * consturcts the mass part of a sprite
 *
 * @param gm a copy of the game manager
 */
Mass::Mass(GameManager *gm) : Sprite(gm)
{
	this->gm = gm;
	isOnGround = false;
}

/**
 * deconsturctor for mass objects
*/
Mass::~Mass()
{
}

/**
 * update the mass with falling and platform collisions
*/
void Mass::update()
{
	applyGravity();
	
	checkPlatformCollision();

	Sprite::update();
	
}

/**
 * makes the mass fall with grvvity
*/
void Mass::applyGravity()
{
	double test = (gravity * (SDL_GetTicks() - lastTimeY)/1000.0);
	yVelocity += test;
	if (yVelocity > terminalVelocity){
		yVelocity = terminalVelocity;
	}

}

/**
 *	check for collisions with platforms and acts on the collisions
*/
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

/**
 * checks if the current rect is over the given rect
 *
 * @param tempRect the rect to check against
 *
 * @return true if over rect false if under
*/
bool Mass::isOverRect(SDL_Rect tempRect)
{
	if (rect.y + rect.h <= tempRect.y){
		return true;
	}
	return false;
}

/**
 * checks if the current rect is under the given rect
 *
 * @param tempRect the rect to check against
 *
 * @return true if under rect false if over
*/
bool Mass::isUnderRect(SDL_Rect tempRect)
{

	if (tempRect.y <= rect.y + rect.h){
		return true;
	}

	return false;
}

/**
 * checks if the current rect is alligned verticaly with the given rect
 *
 * @param tempRect the rect to check against
 *
 * @return true if alligned rect false if not alligned
*/
bool Mass::isVerticalOfRect(SDL_Rect tempRect)
{
	if (tempRect.x + tempRect.w > rect.x &&tempRect.x < rect.x + rect.w){
		return true;
	}
	return false;
}

/**
 * not used but is needed as it is a virtual
*/
void Mass::animationEnd()
{
}
