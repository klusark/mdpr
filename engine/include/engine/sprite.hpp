#ifndef sprite_hpp
#define sprite_hpp
#include <map>
#include <iostream>
#include <fstream>

namespace engine
{
	class spriteInterface;
	class Sprite
	{
	public:
		Sprite(std::string name, std::ifstream &spriteFile);
		Sprite(std::string name);
		virtual ~Sprite();
		virtual void update();
		void addInterface(engine::spriteInterface *interfaces);
		bool isInterfaceAdded(std::string interfaceName);
		std::string name;
		std::map<std::string, engine::spriteInterface *> Interfaces;
	};
}
#endif
