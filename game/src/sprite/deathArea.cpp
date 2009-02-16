#include <SFML/Graphics/Image.hpp>

#include "../enumerations.hpp"
#include "genericSprite.hpp"
#include "deathArea.hpp"
#include "../crc.hpp"
#include "spriteManager.hpp"

sf::Image DeathArea::Image;

DeathArea::DeathArea(const std::string &name, sf::IntRect rect)
	:	genericSprite(name, "DeathArea", Image),
		collisionChecked(false)
{
	spriteType = deathArea;
	collisionRect = rect;
	nonNetworked = true;

}

DeathArea::~DeathArea()
{

}

void DeathArea::update()
{
	genericSprite::update();
}

void DeathArea::draw()
{
}
