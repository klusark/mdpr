#include "spriteManager.hpp"
#include "spriteCollision.hpp"
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
		if (iter->second->spriteType == platform){
			int height = Sprites[spriteID]->currentAnimation->collisionRect.Bottom;
			int left = Sprites[spriteID]->currentAnimation->collisionRect.Left;
			int width = Sprites[spriteID]->currentAnimation->collisionRect.GetWidth();
			sf::Vector2f otherPosition = iter->second->GetPosition();

			if (infos[spriteID]->y + height <= otherPosition.y){
				if (Sprites[spriteID]->GetPosition().x + width + left >= otherPosition.x && Sprites[spriteID]->GetPosition().x <= otherPosition.x + 10){
					if (Sprites[spriteID]->GetPosition().y + height >= otherPosition.y){
						Sprites[spriteID]->SetY(otherPosition.y - height);
					}
				}
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

