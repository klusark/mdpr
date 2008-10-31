#ifndef engine_hpp
#define engine_hpp
#include "dataTypes.hpp"
namespace engine{
	EngineLib bool initEngine();
	EngineLib bool quit();
	extern EngineLib void eventLoop();
	extern EngineLib void mainLoop();
	EngineLib Rect makeRect(int x, int y, unsigned int w, unsigned int h);
}
#endif