#include "engineLib.hpp"
#include "engine.hpp"
#include "window.hpp"
#include "dataTypes.hpp"
#include "sprite.hpp"
#include "spriteManager.hpp"
#include "collision.hpp"
#include "network.hpp"
#include <iostream>
#include <map>

namespace engine{
	/**
	 * Initializes the engine and checks the commandline args
	 * @param argc the argc from main
	 * @param argv the argv from main
	 */
	EngineLib bool initEngine(int argc, char* argv[])
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			printf("Unable to initialize SDL: %s\n", SDL_GetError());
			return false;
		}

		if (network::initNetwork() == false){
			return false;
		}
		bool startServer = false;
		//check command line args
		for (int i = 1; i < argc; ++i){
			if (strcmp(argv[i], "--port") == 0 || strcmp(argv[i], "-p") == 0){
				unsigned short tempPort = static_cast<unsigned short>(atoi(argv[i+1]));
				if (tempPort > 1024){
					network::port = tempPort;
				}else{
					std::cout<<"Error in port";
				}
			}
			if (strcmp(argv[i], "--server") == 0 || strcmp(argv[i], "-s") == 0){
				startServer = true;
				
			}
		}
		//makes sure that the options are all done before the server starts.
		if (startServer){
			SDL_CreateThread(network::startServer, 0);
		}
		network::connect();
		return true;
	}

	/**
	 * Function to run when quitting the program
	 */
	EngineLib bool quit()
	{
		SDL_Quit();
		network::destoryNetwork();
		return true;
	}

	/**
	 * 
	 */
	EngineLib void eventLoop()
	{
		SDL_Event events;
		while (SDL_PollEvent(&events)){
			switch(events.type){
				case SDL_VIDEORESIZE:
					// handle resize event
					window::windowResize(events.resize.w, events.resize.h);
					break;
				case SDL_QUIT:
					// handle quit event
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

	/**
	 * The games main loop. MUST be run one per frame.
	 */
	EngineLib void mainLoop()
	{
		// These are to calculate our fps 
		static int T0     = 0;
		static int Frames = 0;
		eventLoop();

		spriteManager::update();


		window::draw();

		collision::update();

		// Gather our frames per second
		Frames++;
		int t = SDL_GetTicks();
		if (t - T0 >= 5000) {
			float seconds = (t - T0) / 1000.0f;
			float fps = Frames / seconds;
			printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
			T0 = t;
			Frames = 0;
		
		}
	}

	/**
	 * Makes a rect
	 * @param x the x position
	 * @param y the y position
	 * @param w the width
	 * @param h the height
	 */
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
