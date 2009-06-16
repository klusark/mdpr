#ifndef spriteManager_hpp
#define spriteManager_hpp

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include "spriteCollision.hpp"
#include "genericSprite.hpp"
#include "effectManager.hpp"
#include "network/packets.hpp"

class spriteManager
{
public:
	spriteManager();
	~spriteManager();
	typedef std::map<unsigned short, boost::shared_ptr<genericSprite> > spriteContainer;
	spriteContainer Sprites;

	typedef std::map<unsigned short, std::string> spriteTypeContainer;
	spriteTypeContainer SpriteTypes;

	typedef std::map<unsigned short, animationCreationPacket> animationPacketContainer;
	animationPacketContainer Animations;

	void registerSprite(boost::shared_ptr<genericSprite> sprite);
	void update();
	bool isActive();
	void setActive(bool toggle);
	void removeSprite(unsigned int spriteID);
	void removeSprite(std::string spriteID);
	boost::mutex spriteMutex;
	spriteCollision collision;
	void spawn(boost::shared_ptr<genericSprite> spriteToSpawn);

	EffectManager myEffectManager;

private:
    bool active;
	
	
};

extern spriteManager sprite;


#endif // #ifndef spriteManager_hpp
