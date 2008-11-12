#ifndef spriteinput_hpp
#define spriteinput_hpp
#include "spriteInterface.hpp"
#include "sprite.hpp"
#include <string>
namespace engine
{
	class Input : public spriteInterface
	{
	public:
		EngineLib Input();
		virtual ~Input();
		void update();
		std::string getName();
		void EngineLib addInput(std::string keyname, int key);
	};
}
#endif
