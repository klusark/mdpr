#include "Bubble.hpp"

Bubble::Bubble(GameManager *gm) : Sprite(gm)
{
	this->gm = gm;
}

Bubble::~Bubble()
{
}

void Bubble::update()
{
	Sprite::update();
}
