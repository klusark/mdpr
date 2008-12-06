#ifndef spriteManager_hpp
#define spriteManager_hpp
#include <string>
#include <map>
#include "sprite.hpp"
namespace engine
{
	namespace spriteManager
	{
		extern std::map<std::string, Sprite *> Sprites;
		void registerSprite(engine::Sprite *sprite);
		void update();
	}
}
#endif
