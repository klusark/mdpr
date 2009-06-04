#include <boost/shared_ptr.hpp>
#include "../sprite/genericSprite.hpp"
#include "../sprite/spriteManager.hpp"
#include "../sprite/selectionArea.hpp"
#include "../helpers.hpp"
#include "powerUpManager.hpp"
#include "gun.hpp"

RegisterPowerup RegisterGun("gun");

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
		owner->changeAnimation("shoot");
		justShot = true;
		owner->keyLock = true;
		owner->animationLock = true;
		
		//todo: do some name checking to make sure there are no other death areas with the same name
		sf::IntRect newRect(0, int(owner->GetPosition().y) + 12, 0, int(owner->GetPosition().y) + 24);
		if (!owner->flipped){
			newRect.Left = int(owner->GetPosition().x) + 24;
			newRect.Right = 640;
		}else{
			newRect.Left = -640;
			newRect.Right = int(owner->GetPosition().x);
		}
		boost::shared_ptr<genericSprite> newSelectionArea(new selectionArea("gunShotSelectArea", newRect));
		dynamic_cast<selectionArea *>(newSelectionArea.get())->typeToSelect = player;
		mySelectionArea = newSelectionArea;
		sprite.registerSprite(mySelectionArea);
	}
}

void Gun::update()
{
	if (justShot){
		if (dynamic_cast<selectionArea *>(mySelectionArea.get())->collisionChecked){

			sprite.removeSprite(stringToCRC(mySelectionArea->name));
			//mySelectionArea = 0;
		}
		if (clock.GetElapsedTime() > 0.3f){
			justShot = false;
			owner->keyLock = false;
			owner->animationLock = false;
		}
	}
}
