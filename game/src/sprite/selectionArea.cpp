#include <SFML/Graphics/Image.hpp>

#include "../enumerations.hpp"
#include "genericSprite.hpp"
#include "selectionArea.hpp"
#include "../helpers.hpp"
#include "spriteManager.hpp"

sf::Image selectionArea::Image;

selectionArea::selectionArea(const std::string &name, sf::IntRect rect)
	:	genericSprite(name, "selectionArea", Image),
		collisionChecked(false)
{
	spriteType = selectionarea;
	collisionRect = rect;
	nonNetworked = true;

}

selectionArea::~selectionArea()
{

}

void selectionArea::update()
{
	genericSprite::update();
}

void selectionArea::draw()
{
}
