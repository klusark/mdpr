#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include <SFML/Graphics.hpp>

#include <map>
#include "helpers.hpp"
#include "clientSprite.hpp"

#include "clientSpriteManager.hpp"

ClientSpriteManager sprite;

ClientSpriteManager::ClientSpriteManager()
	:	active(false),
		collision(Sprites)
#ifdef SERVER
		,myEffectManager(&sprite)
#endif //#ifdef SERVER
{
}

ClientSpriteManager::~ClientSpriteManager()
{
}

void ClientSpriteManager::registerSprite(boost::shared_ptr<ClientSprite> sprite)
{

	boost::mutex::scoped_lock lock(spriteMutex);
	Sprites[stringToCRC(sprite->name)] = sprite;
}

void ClientSpriteManager::update()
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

void ClientSpriteManager::draw(sf::RenderWindow &App)
{
    spriteContainer::iterator iter;
	for(iter = Sprites.begin(); iter != Sprites.end(); ++iter){
		iter->second->draw(App);
		
	}
}

void ClientSpriteManager::removeSprite(unsigned int spriteID)
{
	spriteContainer::iterator spriteToErase = Sprites.find(spriteID);
	if (spriteToErase != Sprites.end()){
		Sprites.erase(spriteToErase);
	}
}

void ClientSpriteManager::removeSprite(std::string spriteID)
{
	removeSprite(stringToCRC(spriteID));
}

void ClientSpriteManager::spawn(boost::shared_ptr<genericSprite> spriteToSpawn)
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

bool ClientSpriteManager::isActive()
{
    return active;
}

void ClientSpriteManager::setActive(bool toggle)
{
    active = toggle;
}
