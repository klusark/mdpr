#ifndef input_hpp
#define input_hpp
#include "sprite.hpp"
namespace engine
{
	class  Input
	{
	public:
		EngineLib Input();
		virtual EngineLib ~Input();
		virtual void EngineLib update();
	};
}
#endif
