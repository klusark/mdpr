#include <SFML\System.hpp>
#include "spriteManager.hpp"
#include "spriteCollision.hpp"
#include "deathArea.hpp"
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
		if (Sprites[spriteID]->spriteType == player){
			if (iter->second->spriteType == platform){
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
		}else if (Sprites[spriteID]->spriteType == deathArea){
			if (iter->second->spriteType == player){
				sf::IntRect collisionRect = iter->second->currentAnimation->AnimationInfo.collisionRect;
				collisionRect.Offset(int(iter->second->GetPosition().x), int(iter->second->GetPosition().y));
				DeathArea *death = dynamic_cast<DeathArea *>(Sprites[spriteID].get());
				if (death->collisionRect.Intersects(collisionRect)){
					std::cout << "1";
					
				}
				death->collisionChecked = true;
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

