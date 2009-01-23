#include <SFML/Graphics/Image.hpp>

#include "bubble.hpp"
#include "genericSprite.hpp"
#include "../network/packets.hpp"
#include "../crc.hpp"

sf::Image Bubble::Image;

Bubble::Bubble(const std::string &name)
	:	genericSprite(name, "bubble", Image),
		powerup("powerup")
{
	spriteType = bubble;
	CRC crc;
	changeAnimation(crc.stringToShort("bubble"));

	setYVelocity(400.0f);
	setXVelocity(400.0f);

}

Bubble::~Bubble()
{

}

void Bubble::update()
{
	sf::Vector2f position = GetPosition();
	if (position.x >= 640 - 16 || position.x < 0){
		setXVelocity(-getXVelocity());
		if (position.x < 0){
			SetX(1);
		}else if (position.x >= 640 - 16){
			SetX(640 - 15);
		}
	}
	if (position.y >= 400 - 16 || position.y < 0){
		setYVelocity(-getYVelocity());
		if (position.y < 0){
			SetY(1);
		}else if (position.y >= 400 - 16){
			SetY(400 - 15);
		}
	}
	powerup.update();
	genericSprite::update();
}
