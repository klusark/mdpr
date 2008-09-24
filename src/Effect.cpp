#include "Effect.hpp"

/**
 * consturcts the effect sprite
 */
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
void Effect::animationEnd()
{
}
