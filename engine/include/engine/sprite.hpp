#ifndef sprite_hpp
#define sprite_hpp

#include <map>

namespace engine
{
	class spriteInterface;
	class Sprite
	{
	public:
		EngineLib Sprite(std::string name);
		virtual ~Sprite();
		virtual void update();
		EngineLib void addInterface(engine::spriteInterface *interfaces);
		std::string name;
		std::map<std::string, engine::spriteInterface *> Interfaces;
	};
}
#endif
