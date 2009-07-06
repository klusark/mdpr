#include <Poco/SharedPtr.h>

#include <map>

#include "helpers.hpp"
#include "genericSprite.hpp"
#include "player.hpp"
#include "spriteCollision.hpp"

#include "spriteManager.hpp"

spriteManager sprite;

spriteManager::spriteManager()
	:	active(false),
		collision(Sprites),
		myEffectManager(&sprite)
{
}

spriteManager::~spriteManager()
{
}

void spriteManager::registerSprite(Poco::SharedPtr<genericSprite> sprite)
{
	//boost::mutex::scoped_lock lock(spriteMutex);

	Sprites[stringToCRC(sprite->name)] = sprite;
}

void spriteManager::update()
{
	
	collision.before();
	spriteContainer::iterator iter;
	for(iter = Sprites.begin(); iter != Sprites.end(); ++iter){
		iter->second->update();

		if (iter->second->currentState == readyToSpawnState){
			spawn(iter->second);
		}
		collision.update(iter->first);

	}
}

void spriteManager::removeSprite(unsigned int spriteID)
{
	spriteContainer::iterator spriteToErase = Sprites.find(spriteID);
	if (spriteToErase != Sprites.end()){
		Sprites.erase(spriteToErase);
	}
}

void spriteManager::removeSprite(std::string spriteID)
{
	removeSprite(stringToCRC(spriteID));
}

void spriteManager::spawn(Poco::SharedPtr<genericSprite> spriteToSpawn)
{
	spriteToSpawn->currentState = aliveState;
	spriteToSpawn->SetX(50);
	spriteToSpawn->SetY(76);

	Position pos = spriteToSpawn->GetPosition();
	myEffectManager.addEffect(spriteToSpawn->spawnEffect, pos.x, pos.y);
}

bool spriteManager::isActive()
{
    return active;
}

void spriteManager::setActive(bool toggle)
{
    active = toggle;
}
