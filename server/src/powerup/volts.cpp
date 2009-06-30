#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "volts.hpp"

RegisterPowerup RegisterVolts("volts");

Volts::Volts(genericSprite *owner)
	:	genericPowerUp(owner)
{
}

Volts::~Volts()
{
}

void Volts::onActionKey()
{
}

void Volts::update()
{
}
