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
		
			
			if (dedicated){
				return true;
			}
			window::screenWidth = screenWidth;
			window::screenHeight = screenHeight;
			window::bitsPerPixel = bitsPerPixel;
			if (!SDL_WasInit(SDL_INIT_VIDEO)){
				std::cout<<"SDL could not be initializeed"<<std::endl;
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


			//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			if (fullScreenFlag){
			}



			SDL_WM_SetCaption(title.c_str(), title.c_str());

			SDL_ShowCursor(SDL_DISABLE);

			if (SDL_SetVideoMode(screenWidth, screenHeight, 0, SDL_OPENGL) == 0){
				std::cout<<"error";
				throw 1;
			}		

			SDL_EnableUNICODE(1);

			SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);


			
			glMatrixMode (GL_PROJECTION);
			glOrtho (0, screenWidth, screenHeight, 0, 0, 1);
			glMatrixMode (GL_MODELVIEW);

			//

			//windowResize(screenWidth, screenHeight);
			glEnable(GL_TEXTURE_2D);
			glClearColor(0.0f,0.0f,0.0f,1.0f);
			glViewport(0,0, screenWidth,screenHeight);

			//gluPerspective(45.0, screenWidth/screenHeight, 0.1,100.0);

			glClear(GL_COLOR_BUFFER_BIT);



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
			if (dedicated){
				return;
			}
			
			//glLoadIdentity();
			
			Rect rect = engine::makeRect(22, 55, 24, 24);
			

			engine::graphics::drawTexturedQuad(rect, graphics::textures["run0"]);

			// Draw it to the screen
			
		}
	}
}
