#include "GameManager.hpp"
#include "Bubble.hpp"

Bubble::Bubble(GameManager *gm) : Sprite(gm)
{
	this->gm = gm;
	rect.h = 16;
	rect.w = 16;
	rect.x = 16;
	rect.y = 16;

	SDL_Surface *frames[] = {gm->images["bubble0"], gm->images["bubble1"], gm->images["bubble2"]};
	Animation bubbleAnimation = makeAnimaion(3, 100, frames);

	currentAnimation = bubbleAnimation;

}

Bubble::~Bubble()
{
}

void Bubble::update()
{
	Sprite::update();

	move(5, 5);
	if (rect.x > gm->height)
		rect.x = gm->height-16;
	if (rect.y > gm->width)
		rect.y = gm->width-16;
}
