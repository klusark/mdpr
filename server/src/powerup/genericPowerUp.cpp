#include <iostream>
#include "sprite/genericSprite.hpp"
#include "genericPowerUp.hpp"

genericPowerUp::genericPowerUp(genericSprite *newowner)
{
	owner = newowner;
}

genericPowerUp::~genericPowerUp()
{
}

void genericPowerUp::onActionKey()
{
	std::cout << "Improper Use" << std::endl;
}

void genericPowerUp::update()
{
	std::cout << "Improper Use" << std::endl;
}