#include "powerup.hpp"
#include "genericSprite.hpp"
#include "network/packets.hpp"
#include "helpers.hpp"

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

GenericSprite::collidesWithContainer PowerUp::getCollidesWith()
{
	static GenericSprite::collidesWithContainer colidesWith;
	static bool test;
	if (!test){
		colidesWith.insert(stringToCRC("test"));
	}
	return colidesWith;
}
