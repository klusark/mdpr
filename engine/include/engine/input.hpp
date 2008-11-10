#ifndef input_hpp
#define input_hpp
#include "spriteInterface.hpp"
#include "sprite.hpp"
#include <string>
namespace engine
{
	class Input : public spriteInterface
	{
	public:
		EngineLib Input();
		virtual EngineLib ~Input();
		virtual void EngineLib update();
		void EngineLib addInput(std::string keyname, int key);
	};
}
#endif
