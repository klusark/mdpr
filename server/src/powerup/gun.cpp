#include <Poco/SharedPtr.h>
#include "sprite/genericSprite.hpp"
#include "sprite/spriteManager.hpp"
#include "sprite/selectionArea.hpp"
#include "powerUpManager.hpp"
#include "gun.hpp"
#include "helpers.hpp"

RegisterPowerup RegisterGun("gun");

Gun::Gun(GenericSprite *owner)
	:	genericPowerUp(owner),
		justShot(false)
{
}

Gun::~Gun()
{
}

void Gun::onActionKey()
{
	if (!justShot && owner->onGround){
		clock.Reset();
		owner->changeAnimation("shoot");
		justShot = true;
		owner->keyLock = true;
		owner->animationLock = true;
		
		//todo: do some name checking to make sure there are no other selection areas with the same name
		sf::IntRect newRect(0, int(owner->GetY() + 6), 0, int(owner->GetY()) + 8);
		if (!owner->flipped){
			newRect.Left = int(owner->GetX()) + 24;
			newRect.Right = 640;
		}else{
			newRect.Left = -640;
			newRect.Right = int(owner->GetX());
		}
		Poco::SharedPtr<GenericSprite> newSelectionArea(new selectionArea("gunShotSelectArea", newRect));
		dynamic_cast<selectionArea *>(newSelectionArea.get())->typeToSelect = playerType;
		mySelectionArea = newSelectionArea;
		sprite.registerSprite(mySelectionArea);
	}
}

void Gun::update()
{
	if (justShot){
		selectionArea * temp = dynamic_cast<selectionArea *>(mySelectionArea.get());
		if (temp->collisionChecked){
			if (temp->selectedSprites.size()){
				temp->selectClosest(owner->GetPosition(), true, false)->death(stringToCRC("gun"));
			}
			sprite.removeSprite(mySelectionArea->name);
			//mySelectionArea = 0;
		}
		if (clock.GetElapsedTime() > 0.3f){
			justShot = false;
			owner->keyLock = false;
			owner->animationLock = false;
		}
	}
}
