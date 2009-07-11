#include <Poco/SharedPtr.h>
#include <Poco/Mutex.h>

#include <map>
#include "helpers.hpp"
#include "clientSprite.hpp"

#include "clientSpriteManager.hpp"

Poco::SharedPtr<ClientSpriteManager> sprite;

ClientSpriteManager::ClientSpriteManager()
	:	active(false){
}

ClientSpriteManager::~ClientSpriteManager()
{
}

void ClientSpriteManager::registerSprite(Poco::SharedPtr<ClientSprite> sprite)
{
	Poco::ScopedLock<Poco::Mutex> lock(spriteMutex);
	Sprites[stringToCRC(sprite->name)] = sprite;
}

void ClientSpriteManager::update()
{

	spriteContainer::iterator iter;
	for(iter = Sprites.begin(); iter != Sprites.end(); ++iter){
		iter->second->update();
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

bool ClientSpriteManager::isActive()
{
    return active;
}

void ClientSpriteManager::setActive(bool toggle)
{
    active = toggle;
}
