#ifndef engine_hpp
#define engine_hpp
#include "dataTypes.hpp"
namespace engine{
	extern bool dedicated;
	extern bool initEngine(int argc, char* argv[]);
	extern bool quit();
	extern void eventLoop();
	extern void mainLoop();
	extern void loadSprites();
	extern Rect makeRect(int x, int y, unsigned int w, unsigned int h);
}
#endif
