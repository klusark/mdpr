#ifndef sprite_hpp
#define sprite_hpp
#include <list>
#include <deque>

namespace engine
{
	class spriteInterface;
	class Sprite
	{
	public:
		EngineLib Sprite(std::string name);
		virtual EngineLib ~Sprite();
		virtual EngineLib void update();
		EngineLib void addInterface(engine::spriteInterface *interfaces);
		std::string name;
		std::deque<engine::spriteInterface *> Interfaces;
	};
}
#endif