#ifndef movement_hpp
#define movement_hpp
#include "sprite.hpp"
namespace engine
{
	class  Movement
	{
	public:
		EngineLib Movement();
		virtual EngineLib ~Movement();
		virtual void EngineLib update();
	};
}
#endif
