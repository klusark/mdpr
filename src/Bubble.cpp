#include "GameManager.hpp"
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

	SDL_Surface *frames[] = {gm->images["bubble0"], gm->images["bubble1"], gm->images["bubble2"]};
	Animation *bubbleAnimation = makeAnimaion(3, 100, frames);

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

	if (rect.y > gm->height-rect.h){
		rect.y = static_cast<Sint16>(gm->height-rect.h);
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
