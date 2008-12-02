#include "engineLib.hpp"
#include "collision.hpp"
#include "sprite.hpp"
#include <iostream>
#include <map>
#include "spriteManager.hpp"
#include "dataTypes.hpp"
namespace engine
{
	namespace collision
	{
		void update()
		{
			
			std::map<std::string, Sprite *>::iterator iter;
			for( iter = spriteManager::Sprites.begin(); iter != spriteManager::Sprites.end(); ++iter ) {
				std::map<std::string, engine::spriteInterface *>::iterator iter2;
				//iter2 = iter->second->Interfaces.find("collision");
				
				//if( iter2 != iter->second->Interfaces.end() ){
				//	std::cout << "Value is: " << iter2->second << std::endl;
				//}else{
				//	std::cout << "Key is not in myMap" << std::endl;
				//}
				//iter->second->update();

			}

		}

		/**
		 * Has a collided with b
		 * @param a first rect
		 * @param b second rect
		 */
		bool isCollided(Rect a, Rect b)
		{
			return 0;

		}

		/**
		 * Is a right of b
		 * @param a first rect
		 * @param b second rect
		 */
		bool isRightOf(Rect a, Rect b)
		{
			if (signed(b.w + b.x) < a.x){
				return 1;
			}
			return 0;
		}

		/**
		 * Is a left of b
		 * @param a first rect
		 * @param b second rect
		 */
		bool isLeftOf(Rect a, Rect b)
		{
			if (b.x > signed(a.x + a.w)){
				return 1;
			}
			return 0;
		}

		/**
		 * Is a up of b
		 * @param a first rect
		 * @param b second rect
		 */
		bool isUpOf(Rect a, Rect b)
		{
			if (b.y > signed(a.y + a.h)){
				return 1;
			}
			return 0;
		}

		/**
		 * Is a down of b
		 * @param a first rect
		 * @param b second rect
		 */
		bool isDownOf(Rect a, Rect b)
		{
			if (signed(b.y + b.h) < a.y){
				return 1;
			}
			return 0;
		}

	}
}
