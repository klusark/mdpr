#include "enumerations.hpp"
#include "genericSprite.hpp"
#include "selectionArea.hpp"
#include "helpers.hpp"
#include "spriteManager.hpp"

selectionArea::selectionArea(const std::string &name, sf::IntRect rect)
	:	genericSprite(name, "selectionArea"),
		collisionChecked(false)
{
	spriteType = selectionAreaType;
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
