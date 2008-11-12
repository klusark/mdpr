#ifndef spritecollision_hpp
#define spritecollision_hpp
#include "spriteInterface.hpp"
#include "sprite.hpp"
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
		std::vector<collisionInfo> collisions;
		EngineLib Collision();
		virtual ~Collision();
		void update();
		std::string getName();
		void EngineLib setCollisionType(std::string collisionType);
		void EngineLib Collision::colidesWith(std::string name, unsigned int direction);
		
	};
}
#endif
