#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "mine.hpp"

RegisterPowerup RegisterMine("mine");

Mine::Mine(GenericSprite *owner)
	:	genericPowerUp(owner)
{
}

Mine::~Mine()
{
}

void Mine::onActionKey()
{
}

void Mine::update()
{
}
