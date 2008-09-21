#include "GameManager.hpp"
#include "Bubble.hpp"

Bubble::Bubble(GameManager *gm) : Sprite(gm)
{
	this->gm = gm;
	rect.h = 16;
	rect.w = 16;
	rect.x = 16;
	rect.y = 16;
	Animation bubbleAnimation;
	SDL_Surface *frames[] = {gm->images["bubble0"], gm->images["bubble1"], gm->images["bubble2"]};
	makeAnimaion(bubbleAnimation, 3, 100, frames);
	currentAnimation = bubbleAnimation;
	image = gm->images["bubble0"];
}

Bubble::~Bubble()
{
}

void Bubble::update()
{
	Sprite::update();
}
