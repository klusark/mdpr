#include "engineLib.hpp"
#include "engine.hpp"

namespace engine{
	EngineLib bool initEngine()
	{
		if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
			printf("Unable to initialize SDL: %s\n", SDL_GetError());
			return false;
		}
		return true;

	}



	EngineLib bool quit()
	{
		SDL_Quit();
		return true;
	}
}