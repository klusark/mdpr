#include <SFML/Graphics/Image.hpp>

#include "powerup.hpp"
#include "genericSprite.hpp"
#include "../network/packets.hpp"
#include "../helpers.hpp"

sf::Image PowerUp::Image;

PowerUp::PowerUp(const std::string &name)
	:	genericSprite(name, "powerup", Image)
{
	spriteType = playerType;
	//changeAnimation(stringToCRC("gun"));
	//SetX(125);
	//SetY(125);

}

PowerUp::~PowerUp()
{

}

