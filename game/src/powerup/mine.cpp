#include <boost/shared_ptr.hpp>

#include "../sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "mine.hpp"

RegisterPowerup RegisterMine("mine");

Mine::Mine(genericSprite *owner)
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