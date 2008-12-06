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
		Input();
		virtual ~Input();
		void update();
		std::string getName();
		void addInput(std::string keyname, int key);
	};
}
#endif
