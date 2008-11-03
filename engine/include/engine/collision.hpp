#ifndef collision_hpp
#define collision_hpp
#include "sprite.hpp"
namespace engine
{
	class  Collision
	{
	public:
		EngineLib Collision();
		virtual EngineLib ~Collision();
		virtual void EngineLib update();
	};
}
#endif
