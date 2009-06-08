#include <SFML/Graphics/Image.hpp>

#include "effect.hpp"
#include "genericSprite.hpp"


sf::Image Effect::Image;

Effect::Effect(const std::string &name)
	:	genericSprite(name, "effect", Image)
{

	changeAnimation("Effect");
	spriteType = effectType;
	SetX(50);

}

Effect::~Effect()
{
}
