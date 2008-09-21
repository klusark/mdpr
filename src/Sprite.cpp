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
	gm->clearRect(rect);
	animate();
	gm->addToImageQueue(image, rect);
}

void Sprite::animate()
{
	image = currentAnimation.frames[currentFrame];
	++currentFrame;
	if (currentFrame == currentAnimation.numFrames)
		currentFrame = 0;
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

void Sprite::makeAnimaion(Animation &name, short numFrames, short delay, SDL_Surface *frames[])
{
	name.delay = delay;
	name.numFrames = numFrames;
	for (short i = 0; i<numFrames; ++i){
		name.frames[i] = frames[i];
	}
}
