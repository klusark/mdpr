#include <SFML/Graphics/Image.hpp>

#include "powerup.hpp"
#include "genericSprite.hpp"
#include "../network/packets.hpp"
#include "../crc.hpp"

sf::Image PowerUp::Image;

PowerUp::PowerUp(const std::string &name)
	:	genericSprite(name, "powerup", Image)
{
	spriteType = bubble;
	CRC crc;
	changeAnimation(crc.stringToShort("gun"));

}

PowerUp::~PowerUp()
{

}

