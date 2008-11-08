#ifndef collision_hpp
#define collision_hpp
#include "spriteInterface.hpp"
#include "sprite.hpp"
namespace engine
{
	class  Collision : public spriteInterface
	{
	public:
		EngineLib Collision();
		virtual EngineLib ~Collision();
		virtual void EngineLib update();
	};
}
#endif
