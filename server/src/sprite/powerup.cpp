#include "powerup.hpp"
#include "genericSprite.hpp"
#include "network/packets.hpp"
#include "helpers.hpp"

GenericSprite::collidesWithContainer PowerUp::colidesWith;

PowerUp::PowerUp(const std::string &name)
	:	GenericSprite(name, "powerup")
{
	spriteType = playerType;
	//changeAnimation(stringToCRC("gun"));
	//SetX(125);
	//SetY(125);

}

PowerUp::~PowerUp()
{

}

