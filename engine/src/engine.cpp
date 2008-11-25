#include "engineLib.hpp"
#include "engine.hpp"
#include "window.hpp"
#include "dataTypes.hpp"
#include "sprite.hpp"
#include "spriteManager.hpp"
#include "collision.hpp"
#include "network.hpp"
#include <map>

namespace engine{
	EngineLib bool initEngine(int argc, char* argv[])
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			printf("Unable to initialize SDL: %s\n", SDL_GetError());
			return false;
		}

		if (network::initNetwork() == false){
			return false;
		}

		for (int i = 1; i < argc; ++i){
			if (argv[i] == "--server" || "-s"){
				network::startServer();
			}
		}
		network::connect();
		return true;
	}

	EngineLib bool quit()
	{
		SDL_Quit();
		network::destoryNetwork();
		return true;
	}

	EngineLib void eventLoop()
	{
		SDL_Event events;
		while (SDL_PollEvent(&events)){
			switch(events.type){
				case SDL_ACTIVEEVENT:
					if (events.active.gain == 0){
						window::isActive = false;
					}else{
						window::isActive = true;
					}
					break;
				case SDL_VIDEORESIZE:
					// handle resize event
					window::windowResize(events.resize.w, events.resize.h);
					break;
				case SDL_QUIT:
					// handle quit requests
					throw 1;
					break;
				case SDL_KEYDOWN:
					//network::sendKey
					break;
				case SDL_KEYUP:
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

		spriteManager::update();


		window::draw();

		collision::update();

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
