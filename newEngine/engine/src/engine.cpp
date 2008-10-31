#include "engine.hpp"
#include "window.hpp"
#include "dataTypes.hpp"

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

	EngineLib void eventLoop()
	{
		SDL_Event events;
		while (SDL_PollEvent(&events)){
			switch(events.type){
				case SDL_ACTIVEEVENT:
					if (events.active.gain == 0 )
						window::isActive = false;
					else
						window::isActive = true;
					break;
				case SDL_VIDEORESIZE:
					/* handle resize event */
					window::windowResize(events.resize.w, events.resize.h);
					break;
				case SDL_QUIT:
					/* handle quit requests */
					throw 1;
					break;
				default:
					break;
			}
		}
	}

	EngineLib void mainLoop()
	{
		eventLoop();
		window::draw();

	}

	EngineLib Rect makeRect(int x, int y, unsigned int w, unsigned int h)
	{
		Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		return rect;
	}
}