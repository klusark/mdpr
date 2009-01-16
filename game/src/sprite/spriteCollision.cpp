#include "spriteManager.hpp"
#include "spriteCollision.hpp"
#include <map>

spriteCollision::spriteCollision(spriteContainer &Sprites)
	:	Sprites(Sprites)
{
}

spriteCollision::~spriteCollision()
{
}

void spriteCollision::update(int spriteID)
{

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

