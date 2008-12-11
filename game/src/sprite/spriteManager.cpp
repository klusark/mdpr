/*#include "spriteManager.hpp"
#include <map>
namespace engine
{
	namespace spriteManager
	{
		std::map<std::string, Sprite *> Sprites;

		void registerSprite(Sprite *sprite)
		{
			Sprites[sprite->name] = sprite;
			return;
		}

		void update()
		{
			std::map<std::string, Sprite *>::iterator iter;
			for( iter = spriteManager::Sprites.begin(); iter != spriteManager::Sprites.end(); ++iter ) {
				iter->second->update();

			}
		}
	}
}
*/