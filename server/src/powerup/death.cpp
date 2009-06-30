#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "death.hpp"
#include "helpers.hpp"

RegisterPowerup RegisterDeath("death");

Death::Death(genericSprite *owner)
	:	genericPowerUp(owner)
{
}

Death::~Death()
{
}

void Death::onActionKey()
{
}

void Death::update()
{
	owner->death(stringToCRC("death"));
}
