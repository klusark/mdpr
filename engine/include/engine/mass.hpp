#ifndef mass_hpp
#define mass_hpp
#include "sprite.hpp"
namespace engine
{
	class  Mass
	{
	public:
		EngineLib Mass();
		virtual EngineLib ~Mass();
		virtual void EngineLib update();
	};
}
#endif
