#include "powerup/powerUpManager.hpp"
#include "enumerations.hpp"
#include "helpers.hpp"
#include "genericSprite.hpp"
#include "powerup.hpp"
#include "bubble.hpp"


Bubble::Bubble(const std::string &name)
	:	GenericSprite(name, "bubble"),
		powerup(name+"powerup")
{
	spriteType = bubbleType;

	changeAnimation(stringToCRC("bubble"));

	setYVelocity(100.0f);
	setXVelocity(100.0f);
	//powerup.changeAnimation(PUManage->selectRandom());
}

Bubble::~Bubble()
{

}

void Bubble::update()
{
	
	Position position = GetPosition();
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
	//powerup.update();
	GenericSprite::update();
	powerup.SetPosition(GetPosition());
}

GenericSprite::collidesWithContainer Bubble::getCollidesWith()
{
	static GenericSprite::collidesWithContainer colidesWith;
	static bool test;
	if (!test){
		colidesWith.insert(stringToCRC("test"));
	}
	return colidesWith;
}

