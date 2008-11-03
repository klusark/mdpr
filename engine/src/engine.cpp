#include "engine.hpp"
#include "window.hpp"
#include "dataTypes.hpp"
#include "sprite.hpp"
#include "spriteManager.hpp"
#include <map>

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
		// These are to calculate our fps 
		static GLint T0     = 0;
		static GLint Frames = 0;
		eventLoop();

		std::map<std::string, Sprite *>::iterator iter;
		for( iter = spriteManager::Sprites.begin(); iter != spriteManager::Sprites.end(); ++iter ) {
			iter->second->update();

		}

		window::draw();
		// Gather our frames per second
		Frames++;
		GLint t = SDL_GetTicks();
		if (t - T0 >= 5000) {
			GLfloat seconds = (t - T0) / 1000.0f;
			GLfloat fps = Frames / seconds;
			printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
			T0 = t;
			Frames = 0;
		
		}
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