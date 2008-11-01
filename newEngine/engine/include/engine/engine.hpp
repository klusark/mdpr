#ifndef engine_hpp
#define engine_hpp
#include "dataTypes.hpp"
namespace engine{
	extern EngineLib bool initEngine();
	extern EngineLib bool quit();
	extern EngineLib void eventLoop();
	extern EngineLib void mainLoop();
	extern EngineLib Rect makeRect(int x, int y, unsigned int w, unsigned int h);
}
#endif
