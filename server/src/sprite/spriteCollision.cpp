#include <SFML\System.hpp>
#include "spriteManager.hpp"
#include "spriteCollision.hpp"
#include "selectionArea.hpp"
#include "../network/packets.hpp"
#include <map>
#include <SFML/System/Vector2.hpp>

spriteCollision::spriteCollision(spriteContainer &Sprites)
	:	Sprites(Sprites)
{
}

spriteCollision::~spriteCollision()
{
}

void spriteCollision::update(int spriteID)
{
	spriteContainer::iterator iter;
	for(iter = Sprites.begin(); iter != Sprites.end(); ++iter){
		if (Sprites[spriteID]->spriteType == playerType){
			if (iter->second->spriteType == platformType){
				int height = Sprites[spriteID]->currentAnimation->AnimationInfo.collisionRect.Bottom;
				int left = Sprites[spriteID]->currentAnimation->AnimationInfo.collisionRect.Left;
				int width = Sprites[spriteID]->currentAnimation->AnimationInfo.collisionRect.GetWidth();
				sf::Vector2f otherPosition = iter->second->GetPosition();

				if (infos[spriteID]->y + height <= otherPosition.y){
					if (Sprites[spriteID]->GetPosition().x + width + left >= otherPosition.x && Sprites[spriteID]->GetPosition().x <= otherPosition.x + 10){
						if (Sprites[spriteID]->GetPosition().y + height >= otherPosition.y){
							Sprites[spriteID]->SetY(otherPosition.y - height);
							Sprites[spriteID]->onGround = true;
						}
					}
				}else{
					Sprites[spriteID]->onGround = false;
				}
			}
		}else if (Sprites[spriteID]->spriteType == selectionAreaType){
			selectionArea *area = dynamic_cast<selectionArea *>(Sprites[spriteID].get());
			if (iter->second->spriteType == area->typeToSelect){
				sf::IntRect collisionRect = iter->second->currentAnimation->AnimationInfo.collisionRect;
				collisionRect.Offset(int(iter->second->GetPosition().x), int(iter->second->GetPosition().y));
				
				if (area->collisionRect.Intersects(collisionRect)){
					area->selectedSprites.push_back(iter->second->name);
					
				}
				area->collisionChecked = true;
			}
		}
	}
}

void spriteCollision::before()
{
	infos.clear();

	spriteContainer::iterator iter;
	for(iter = Sprites.begin(); iter != Sprites.end(); ++iter){
		sf::Vector2f position = iter->second->GetPosition();
		boost::shared_ptr<collisionInfo> info(new collisionInfo);
		info->x = position.x;
		info->y = position.y;
		infos[iter->first] = info;

	}
}

