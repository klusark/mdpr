#include <Poco/SharedPtr.h>

#include "powerUpManager.hpp"
#include "boots.hpp"

RegisterPowerup RegisterBoots("boots");

Boots::Boots(GenericSprite *owner)
	:	genericPowerUp(owner)
{
}

Boots::~Boots()
{
}

void Boots::onActionKey()
{
}

void Boots::update()
{
}
