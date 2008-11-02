#include "Effect.hpp"

/**
 * consturcts the effect sprite
 */
Effect::Effect(GameManager *gm) : Sprite(gm)
{
	this->gm = gm;
	bInUse = false;

	animations["bubblestart"] = makeAnimaion(3, 100, "bubblestart0", "bubblestart1", "bubblestart2");
	rect = gm->makeRect(24,24,0,0);
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
	bInUse = false;
}

bool Effect::isInUse()
{
	return bInUse;
}

void Effect::startEffect(std::string name){
	bInUse = true;
	currentAnimation = animations[name];
}
