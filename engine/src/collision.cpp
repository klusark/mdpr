#include "engineLib.hpp"
#include "collision.hpp"
#include "sprite.hpp"
#include <iostream>
#include <map>
#include "spriteManager.hpp"
namespace engine
{
	namespace collision
	{
		void update()
		{
			
			std::map<std::string, Sprite *>::iterator iter;
			for( iter = spriteManager::Sprites.begin(); iter != spriteManager::Sprites.end(); ++iter ) {
				std::map<std::string, engine::spriteInterface *>::iterator iter2;
				iter2 = iter->second->Interfaces.find("collision");
				
				if( iter2 != iter->second->Interfaces.end() ){
					std::cout << "Value is: " << iter2->second << std::endl;
				}else{
					std::cout << "Key is not in myMap" << std::endl;
				}
				//iter->second->update();

			}

		}
	}
}
