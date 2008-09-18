#include "Effect.hpp"

Effect::Effect(GameManager *gm) : Sprite(gm)
{
	this->gm = gm;
}

Effect::~Effect()
{
}

void Effect::update()
{
	Sprite::update();
}
