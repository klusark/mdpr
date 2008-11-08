#ifndef sprite_hpp
#define sprite_hpp
#include <list>
namespace engine
{
	class spriteInterface;
	class Sprite
	{
	public:
		EngineLib Sprite(const char *name);
		virtual EngineLib ~Sprite();
		virtual EngineLib void update();
		EngineLib void addInterface(engine::spriteInterface *interfaces);
		const char *name;
		std::list<engine::spriteInterface *> Interfaces;
	};
}
#endif