#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "hook.hpp"

RegisterPowerup RegisterHook("hook");

Hook::Hook(GenericSprite *owner)
	:	genericPowerUp(owner)
{
}

Hook::~Hook()
{
}

void Hook::onActionKey()
{
}

void Hook::update()
{
}
