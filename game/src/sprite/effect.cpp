#include <SFML/Graphics/Image.hpp>

#include "effect.hpp"
#include "genericSprite.hpp"


sf::Image Effect::Image;

Effect::Effect(const std::string &name)
	:	genericSprite(name, "effect", Image),
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
	genericSprite::update();
	if (currentAnimation->paused && inUse){
		inUse = false;
		SetX(unsigned short(-1));
		SetY(unsigned short(-1));
	}
}