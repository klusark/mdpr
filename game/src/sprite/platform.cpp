#include <SFML/Graphics/Image.hpp>

#include "platform.hpp"
#include "genericSprite.hpp"
#include "../crc.hpp"

sf::Image Platform::Image;

Platform::Platform(const std::string &name)
	:	genericSprite(name, "platform", Image)
{
	CRC crc;
	changeAnimation(crc.stringToShort("platform"));
	spriteType = platform;
	SetX(50);

}

Platform::~Platform()
{
}
