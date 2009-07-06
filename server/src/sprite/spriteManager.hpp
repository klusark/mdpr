#ifndef spriteManager_hpp
#define spriteManager_hpp

#include <map>
#include <string>

#include <Poco/SharedPtr.h>
#include <Poco/Mutex.h>

#include "spriteCollision.hpp"
#include "genericSprite.hpp"
#include "effectManager.hpp"
#include "network/packets.hpp"

class spriteManager
{
public:
	spriteManager();
	~spriteManager();
	typedef std::map<unsigned short, Poco::SharedPtr<genericSprite> > spriteContainer;
	spriteContainer Sprites;

	typedef std::map<unsigned short, std::string> spriteTypeContainer;
	spriteTypeContainer SpriteTypes;

	typedef std::map<unsigned short, animationCreationPacket> animationPacketContainer;
	animationPacketContainer Animations;

	void registerSprite(Poco::SharedPtr<genericSprite> sprite);
	void update();
	bool isActive();
	void setActive(bool toggle);
	void removeSprite(unsigned int spriteID);
	void removeSprite(std::string spriteID);
	Poco::Mutex spriteMutex;
	spriteCollision collision;
	void spawn(Poco::SharedPtr<genericSprite> spriteToSpawn);

	EffectManager myEffectManager;

private:
    bool active;
	
	
};

extern spriteManager sprite;


#endif // #ifndef spriteManager_hpp
