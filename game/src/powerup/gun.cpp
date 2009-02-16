#include <boost/shared_ptr.hpp>
#include "../sprite/genericSprite.hpp"
#include "../sprite/spriteManager.hpp"
#include "../sprite/deathArea.hpp"
#include "../crc.hpp"
#include "gun.hpp"

Gun::Gun(genericSprite *owner)
	:	genericPowerUp(owner),
		justShot(false)
{
}

Gun::~Gun()
{
}

void Gun::onActionKey()
{
	if (!justShot){
		clock.Reset();
		justShot = true;

		owner->changeAnimation("shoot");
		
		//todo: do some name checking to make sure there are no other death areas with the same name
		sf::IntRect newRect(0, int(owner->GetPosition().y)+12, 0, int(owner->GetPosition().y)+24);
		if (!owner->flipped){
			newRect.Left = int(owner->GetPosition().x)+24;
			newRect.Right = 640;
		}else{
			newRect.Left = -640;
			newRect.Right = int(owner->GetPosition().x);
		}
		boost::shared_ptr<genericSprite> newDeathArea(new DeathArea("gunShotDeathArea", newRect));
		myDeathArea = newDeathArea;
		sprite.registerSprite(myDeathArea);
	}
}

void Gun::update()
{
	if (justShot){
		if (dynamic_cast<DeathArea *>(myDeathArea.get())->collisionChecked){
			sprite.removeSprite(CRC().stringToShort(myDeathArea->name));
			//myDeathArea = 0;
		}
		if (clock.GetElapsedTime() > 0.2f){
			justShot = false;
		}
	}
}
