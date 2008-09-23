#include "SDL.h"

#include "GameManager.hpp"
#include "Sprite.hpp"

/**
 * consturcts the sprite
 */
Sprite::Sprite(GameManager *gm)
{
	this->gm = gm;
	currentFrame = 0;
	xMove = 0, yMove = 0;
}

Sprite::~Sprite()
{
}

void Sprite::update()
{

	gm->clearRect(lastRect);
	move();
	animate();
	gm->addToImageQueue(image, rect);
	lastRect = rect;
	moved = false;
}

void Sprite::animate()
{
	if(currentAnimation.delay < (SDL_GetTicks() - lastAnimationTime)){
		lastAnimationTime = SDL_GetTicks();
		++currentFrame;
		if (currentFrame >= currentAnimation.numFrames)
			currentFrame = 0;
		image = currentAnimation.frames[currentFrame];

	}
}

/**
* moves the sprite
*/
void Sprite::move()
{
	if (!moved){
		yMove = (yVelocity * (SDL_GetTicks() - lastTimeY)/1000.0);
		if (yMove > 1 || yMove < -1){
			lastTimeY = SDL_GetTicks();
			rect.y += static_cast<Sint16>(yMove);
		}

		xMove = (xVelocity * (SDL_GetTicks() - lastTimeX)/1000.0);
		if (xMove > 1 || xMove < -1){
			lastTimeX = SDL_GetTicks();
			rect.x += static_cast<Sint16>(xMove);
		}
		moved = true;
	}
}

/**
* sets the collision type of the sprite
* @param collision the type of collision the sprite useses
*/
void Sprite::setCollisionType(collisionTypes collision)
{
	collisionType = collision;
}

Sprite::Animation Sprite::makeAnimaion(short numFrames, Uint16 delay, SDL_Surface *frames[])
{
	Animation animation;
	animation.delay = delay;
	animation.numFrames = numFrames;
	for (short i = 0; i<numFrames; ++i){
		animation.frames[i] = frames[i];
	}
	return animation;
}
