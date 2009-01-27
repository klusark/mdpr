#include <SFML/Graphics/Image.hpp>

#include "powerup.hpp"
#include "genericSprite.hpp"
#include "../network/packets.hpp"
#include "../crc.hpp"

sf::Image PowerUp::Image;

PowerUp::PowerUp(const std::string &name)
	:	genericSprite(name, "powerup", Image)
{
	spriteType = player;
	CRC crc;
	changeAnimation(crc.stringToShort("gun"));
	SetX(125);
	SetY(125);

}

PowerUp::~PowerUp()
{

}

