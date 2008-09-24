
#include "Effect.hpp"

/**
 * consturcts the effect sprite
 */
Effect::Effect(GameManager *gm) : Sprite(gm)
{
	this->gm = gm;
	bInUse = false;

	SDL_Surface *bubblestartFrames[] = {gm->images["bubblestart0"], gm->images["bubblestart1"], gm->images["bubblestart2"]};
	animations["bubblestart"] = makeAnimaion(3, 100, bubblestartFrames);
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