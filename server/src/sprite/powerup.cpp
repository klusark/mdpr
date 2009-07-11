#include "powerup.hpp"
#include "genericSprite.hpp"
#include "network/packets.hpp"
#include "helpers.hpp"

PowerUp::PowerUp(const std::string &name)
	:	genericSprite(name, "powerup")
{
	spriteType = playerType;
	//changeAnimation(stringToCRC("gun"));
	//SetX(125);
	//SetY(125);

}

PowerUp::~PowerUp()
{

}
