#ifndef spriteManager_hpp
#define spriteManager_hpp

#include <map>
#include <string>
#include "genericSprite.hpp"

class spriteManager
{
public:
	spriteManager();
	~spriteManager();
	typedef std::map<std::string, genericSprite *> spriteContainer;
	spriteContainer Sprites;
	void registerSprite(genericSprite *sprite);
	void update();
};

#endif
