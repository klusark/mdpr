#include "Sprite.hpp"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

void Sprite::update()
{
	animate();
}

void Sprite::animate()
{
}

/**
* moves the sprite
* @param x moves the sprite x pixels on the x axis
* @param y moves the sprite y pixels on the y axis
*/
void Sprite::move(short x, short y)
{
}

/**
* sets the collision type of the sprite
* @param collision the type of collision the sprite useses
*/
void Sprite::setCollisionType(collisionTypes collision)
{
	collisionType = collision;
}
