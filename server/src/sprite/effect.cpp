#include <SFML/Graphics/Image.hpp>

#include "effect.hpp"
#include "animation.hpp"

Effect::Effect(const std::string &name)
	:	GenericSprite(name, "effect"),
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