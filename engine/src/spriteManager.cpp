#include "engineLib.hpp"
#include "spriteManager.hpp"
namespace engine
{
	namespace spriteManager
	{
		std::map<std::string, Sprite *> Sprites;

		EngineLib void registerSprite(Sprite *sprite)
		{
			Sprites[sprite->name] = sprite;
			return;
		}
	}
}
