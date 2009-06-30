#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "warp.hpp"

RegisterPowerup RegisterWarp("warp");

Warp::Warp(genericSprite *owner)
	:	genericPowerUp(owner)
{
}

Warp::~Warp()
{
}

void Warp::onActionKey()
{
}

void Warp::update()
{
}
