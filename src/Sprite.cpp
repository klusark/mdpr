#include "SDL.h"

#include "GameManager.hpp"
#include "Sprite.hpp"

Sprite::Sprite(GameManager *gm)
{
	this->gm = gm;
	currentFrame = 0;
}

Sprite::~Sprite()
{
}

void Sprite::update()
{

	gm->clearRect(lastRect);
	animate();
	gm->addToImageQueue(image, rect);
	lastRect = rect;
}

void Sprite::animate()
{
	if(currentAnimation.delay < (SDL_GetTicks() - lastAnimationTime)){
		lastAnimationTime = SDL_GetTicks();
		image = currentAnimation.frames[currentFrame];
		++currentFrame;
		if (currentFrame == currentAnimation.numFrames)
			currentFrame = 0;
	}
}

/**
* moves the sprite
* @param x moves the sprite x pixels on the x axis
* @param y moves the sprite y pixels on the y axis
*/
void Sprite::move(short x, short y)
{
	rect.x += x;
	rect.y += y;
}

/**
* sets the collision type of the sprite
* @param collision the type of collision the sprite useses
*/
void Sprite::setCollisionType(collisionTypes collision)
{
	collisionType = collision;
}

Sprite::Animation Sprite::makeAnimaion( short numFrames, Uint16 delay, SDL_Surface *frames[])
{
	Animation animation;
	animation.delay = delay;
	animation.numFrames = numFrames;
	for (short i = 0; i<numFrames; ++i){
		animation.frames[i] = frames[i];
	}
	return animation;
}
