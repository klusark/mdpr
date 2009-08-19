#include <Poco/SharedPtr.h>

#include <map>

#include "helpers.hpp"
#include "genericSprite.hpp"
#include "player.hpp"
#include "spriteCollision.hpp"

#include "spriteManager.hpp"

SpriteManager sprite;

SpriteManager::SpriteManager():
active(false),
collision(Sprites),
myEffectManager(&sprite)
{
}

SpriteManager::~SpriteManager()
{
}

void SpriteManager::registerSprite(Poco::SharedPtr<GenericSprite> sprite)
{

	Sprites[stringToCRC(sprite->name)] = sprite;
}

void SpriteManager::update()
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

void SpriteManager::removeSprite(unsigned int spriteID)
{
	spriteContainer::iterator spriteToErase = Sprites.find(spriteID);
	if (spriteToErase != Sprites.end()){
		Sprites.erase(spriteToErase);
	}
}

void SpriteManager::removeSprite(std::string spriteID)
{
	removeSprite(stringToCRC(spriteID));
}

void SpriteManager::spawn(Poco::SharedPtr<GenericSprite> spriteToSpawn)
{
	spriteToSpawn->currentState = aliveState;
	spriteToSpawn->SetX(50);
	spriteToSpawn->SetY(76);

	Position pos = spriteToSpawn->GetPosition();
	myEffectManager.addEffect(spriteToSpawn->spawnEffect, pos.x, pos.y);
}

bool SpriteManager::isActive()
{
	return active;
}

void SpriteManager::setActive(bool toggle)
{
	active = toggle;
}
