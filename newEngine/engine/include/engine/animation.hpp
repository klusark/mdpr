#ifndef animaiton_hpp
#define animation_hpp
#include "sprite.hpp"
namespace engine
{
	class EngineLib Animaiton
	{
	public:
		Animaiton();
		virtual ~Animaiton();
		virtual void update();
	};
}
#endif
