#ifndef spritecollision_hpp
#define spritecollision_hpp
#include "spriteInterface.hpp"
#include "sprite.hpp"
#include "dataTypes.hpp"

#include <vector>
namespace engine
{
	class  Collision : public spriteInterface
	{
	public:
		std::string collisionType;

		struct collisionInfo
		{
			int direction;
			std::string name;
		};
		Rect collisionRect;
		std::vector<collisionInfo> collisions;
		Collision();
		virtual ~Collision();
		void update();
		
		std::string getName();
		void setCollisionType(std::string collisionType);
		void colidesWith(std::string name, unsigned int direction);
		
	};
}
#endif
