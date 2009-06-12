#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include <SFML/Graphics.hpp>

#include <map>
#include "../helpers.hpp"
#include "genericSprite.hpp"
#include "player.hpp"
#include "spriteCollision.hpp"

#include "spriteManager.hpp"

spriteManager sprite;

spriteManager::spriteManager()
	:	active(false),
		collision(Sprites)
#ifdef SERVER
		,myEffectManager(&sprite)
#endif //#ifdef SERVER
{
}

spriteManager::~spriteManager()
{
}

void spriteManager::registerSprite(boost::shared_ptr<genericSprite> sprite)
{

	boost::mutex::scoped_lock lock(spriteMutex);
	Sprites[stringToCRC(sprite->name)] = sprite;
}

void spriteManager::update()
{
#ifdef SERVER
	collision.before();
#endif
	spriteContainer::iterator iter;
	for(iter = Sprites.begin(); iter != Sprites.end(); ++iter){
		iter->second->update();
#ifdef SERVER
		if (iter->second->currentState == readyToSpawnState){
			spawn(iter->second);
		}

		collision.update(iter->first);
#endif
	}
}

void spriteManager::draw(sf::RenderWindow &App)
{
    spriteContainer::iterator iter;
	for(iter = Sprites.begin(); iter != Sprites.end(); ++iter){
		iter->second->draw(App);
		
	}
}

void spriteManager::removeSprite(unsigned int spriteID)
{
	spriteContainer::iterator spriteToErase = Sprites.find(spriteID);
	if (spriteToErase != Sprites.end()){
		Sprites.erase(spriteToErase);
	}
}

void spriteManager::spawn(boost::shared_ptr<genericSprite> spriteToSpawn)
{
#ifdef SERVER
	std::cout<<"SPAWN"<<std::endl;
	spriteToSpawn->currentState = aliveState;
	spriteToSpawn->SetX(50);
	spriteToSpawn->SetY(50);

	sf::Vector2f pos = spriteToSpawn->GetPosition();
	myEffectManager.addEffect(spriteToSpawn->spawnEffect, pos.x, pos.y);
#endif
}

bool spriteManager::isActive()
{
    return active;
}

void spriteManager::setActive(bool toggle)
{
    active = toggle;
}
