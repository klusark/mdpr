#include "Bubble.hpp"

/**
 * consturcts the bubble sprite
 */
Bubble::Bubble(GameManager *gm) : Sprite(gm)
{
	this->gm = gm;
	rect.h = 16;
	rect.w = 16;
	rect.x = 16;
	rect.y = 16;

	Animation *bubbleAnimation = makeAnimaion(3, 100, "bubble0", "bubble1", "bubble2");

	currentAnimation = bubbleAnimation;
	xVelocity = 32;
	yVelocity = 32;
}

Bubble::~Bubble()
{
}

void Bubble::update()
{

	Sprite::update();
	
	if (rect.x > gm->width-rect.w){
		rect.x = static_cast<Sint16>(gm->width-rect.w);
		xVelocity = -xVelocity;
	}

	if (rect.x < 0){
		rect.x = static_cast<Sint16>(0);
		xVelocity = -xVelocity;
	}

	if (rect.y > gm->height-rect.h-16){
		rect.y = static_cast<Sint16>(gm->height-rect.h-16);
		yVelocity = -yVelocity;
	}

	if (rect.y < 0){
		rect.y = static_cast<Sint16>(0);
		yVelocity = -yVelocity;
	}

}
void Bubble::animationEnd()
{
}
