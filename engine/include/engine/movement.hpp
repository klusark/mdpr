#ifndef movement_hpp
#define movement_hpp
#include "spriteInterface.hpp"
#include "sprite.hpp"
namespace engine
{
	class  Movement : public spriteInterface
	{
	public:
		EngineLib Movement();
		virtual EngineLib ~Movement();
		virtual void EngineLib update();
	};
}
#endif
