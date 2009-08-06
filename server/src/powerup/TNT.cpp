#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "TNT.hpp"

RegisterPowerup RegisterTNT("TNT");

TNT::TNT(GenericSprite *owner)
	:	genericPowerUp(owner)
{
}

TNT::~TNT()
{
}

void TNT::onActionKey()
{
}

void TNT::update()
{
}
