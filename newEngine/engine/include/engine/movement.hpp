#ifndef movement_hpp
#define movement_hpp
#include "sprite.hpp"
namespace engine
{
	class EngineLib Movement
	{
	public:
		Movement();
		virtual ~Movement();
		virtual void update();
	};
}
#endif
