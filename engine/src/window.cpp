#include "engineLib.hpp"
#include "graphics.hpp"
#include "window.hpp"
#include "engine.hpp"
#include <iostream>

namespace engine{
	namespace window{
		bool isActive = true;
		int videoFlags;
		int screenWidth;
		int screenHeight;
		int bitsPerPixel;

		EngineLib bool createWindow(int screenWidth, int screenHeight, int bitsPerPixel, std::string title, bool fullScreenFlag)
		{
			window::screenWidth = screenWidth;
			window::screenHeight = screenHeight;
			window::bitsPerPixel = bitsPerPixel;
			if (!SDL_WasInit(SDL_INIT_VIDEO)){
				printf("SDL not initializeed\n");
				return false;
			}
		    videoFlags  = SDL_OPENGL;          // Enable OpenGL in SDL 
			videoFlags |= SDL_GL_DOUBLEBUFFER; // Enable double buffering 
			videoFlags |= SDL_HWPALETTE;       // Store the palette in hardware 
			//videoFlags |= SDL_RESIZABLE;       // Enable window resizing 

			const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo( );
			if (videoInfo->hw_available){
				videoFlags |= SDL_HWSURFACE;
			}else{
				videoFlags |= SDL_SWSURFACE;
			}

			videoFlags |= SDL_HWACCEL;


			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 );

			if (fullScreenFlag){
			}

			//SDL_SetVideoMode(screenWidth, screenHeight, bitsPerPixel, videoFlags);

			SDL_WM_SetCaption(title.c_str(), title.c_str());

			windowResize(screenWidth, screenHeight);
			glEnable(GL_TEXTURE_2D);
			return true;
		}

		void windowResize(int width, int height)
		{
			SDL_SetVideoMode(width, height, bitsPerPixel, videoFlags);
			
			glMatrixMode (GL_PROJECTION);
			glOrtho (0, screenWidth, screenHeight, 0, 0, 1);
			glMatrixMode (GL_MODELVIEW);

			glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
			
		}

		void draw()
		{
			glLoadIdentity();
			Rect rect = engine::makeRect(22, 55, 24, 24);
			std::map<std::string, unsigned int>::iterator iter = graphics::textures.begin();

			iter = graphics::textures.find("runs");
			if( iter != graphics::textures.end() ) 
				std::cout << "Value is: " << iter->second << std::endl;
			else
				std::cout << "Key is not in myMap" << std::endl;
			//std::cout<<graphics::textures.end<<std::endl;
			engine::graphics::drawTexturedQuad(rect, graphics::textures["run0"]);

			// Draw it to the screen
			SDL_GL_SwapBuffers();
		}
	}
}
