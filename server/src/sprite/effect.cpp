#include "effect.hpp"
#include "animation.hpp"
#include "helpers.hpp"

Effect::Effect(const std::string &name):
GenericSprite(name, "effect"),
inUse(false)
{

	changeAnimation("blank");
	spriteType = effectType;
	currentState = aliveState;

}

Effect::~Effect()
{
}

void Effect::update()
{
	GenericSprite::update();
	if (currentAnimation->paused && inUse){
		inUse = false;
		currentAnimation->reset();
		changeAnimation("blank");
		SetX((unsigned short)-1);
		SetY((unsigned short)-1);
	}
}

GenericSprite::collidesWithContainer Effect::getCollidesWith()
{
	GenericSprite::collidesWithContainer colidesWith;
	colidesWith.insert(stringToCRC("test"));
	return colidesWith;
}
