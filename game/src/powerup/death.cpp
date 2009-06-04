#include <boost/shared_ptr.hpp>

#include "../sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "death.hpp"

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
	owner->die();
}
