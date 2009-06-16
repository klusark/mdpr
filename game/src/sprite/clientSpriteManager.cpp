#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include <SFML/Graphics.hpp>

#include <map>
#include "helpers.hpp"
#include "clientSprite.hpp"

#include "clientSpriteManager.hpp"

ClientSpriteManager sprite;

ClientSpriteManager::ClientSpriteManager()
	:	active(false){
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
