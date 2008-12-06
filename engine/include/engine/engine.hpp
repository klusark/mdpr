#ifndef engine_hpp
#define engine_hpp
#include "dataTypes.hpp"
namespace engine{
	extern bool dedicated;
	extern EngineLib bool initEngine(int argc, char* argv[]);
	extern EngineLib bool quit();
	extern void eventLoop();
	extern EngineLib void mainLoop();
	extern EngineLib void loadSprites();
	extern Rect makeRect(int x, int y, unsigned int w, unsigned int h);
}
#endif
