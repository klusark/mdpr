#include <Poco/Util/Application.h>
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
	Poco::Util::Application::instance().logger().warning("Improper Use");
	//std::cout << "Improper Use" << std::endl;
}

void genericPowerUp::update()
{
	Poco::Util::Application::instance().logger().warning("Improper Use");
	//std::cout << "Improper Use" << std::endl;
}