#ifndef mass_hpp
#define mass_hpp
#include "spriteInterface.hpp"
#include "sprite.hpp"
namespace engine
{
	class  Mass : public spriteInterface
	{
	public:
		EngineLib Mass();
		virtual EngineLib ~Mass();
		virtual void EngineLib update();
	};
}
#endif
