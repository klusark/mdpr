#include "engineLib.hpp"
#include "window.hpp"

namespace engine{
	namespace window{
		EngineLib bool createWindow(int screenWidth, int screenHeight, int bitsPerPixel, const char * title, bool fullScreenFlag)
		{
			if (!SDL_WasInit(SDL_INIT_VIDEO)){
				printf("SDL not initializeed\n");
				return false;
			}

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 );

			if (fullScreenFlag)
				SDL_SetVideoMode(screenWidth, screenHeight, bitsPerPixel, SDL_OPENGL | SDL_RESIZABLE | SDL_FULLSCREEN);
			else
				SDL_SetVideoMode(screenWidth, screenHeight, bitsPerPixel, SDL_OPENGL | SDL_RESIZABLE);

			SDL_WM_SetCaption(title, title);
			

			glEnable( GL_TEXTURE_2D );
 
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			 
			glViewport( 0, 0, screenWidth, screenHeight );
			 
			glClear( GL_COLOR_BUFFER_BIT );
			 
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			 
			glOrtho(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);
			 
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();

			return true;
		}
		void window_resized(int w, int h)
{
	SDL_SetVideoMode(w, h, 16, SDL_OPENGL | SDL_RESIZABLE);
			glEnable( GL_TEXTURE_2D );
 
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			 
			glViewport( 0, 0, w, h );
			 
			glClear( GL_COLOR_BUFFER_BIT );
			 
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			 
			glOrtho(0.0f, w, h, 0.0f, -1.0f, 1.0f);
			 
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();
}

		EngineLib void eventLoop()
		{
			SDL_Event events;
			while (SDL_PollEvent(&events)){
				if (events.type == SDL_QUIT){
					//quit the game
					throw 1; 
				}else if (events.type == SDL_VIDEORESIZE){
					window_resized(events.resize.w, events.resize.h);
				}
			}
		}

		EngineLib void mainLoop()
		{
			glBegin( GL_QUADS );
				//Top-left vertex (corner)
				glTexCoord2i( 0, 0 );
				glVertex3f( 100, 100, 0.0f );
			 
				//Bottom-left vertex (corner)
				glTexCoord2i( 1, 0 );
				glVertex3f( 228, 100, 0 );
			 
				//Bottom-right vertex (corner)
				glTexCoord2i( 1, 1 );
				glVertex3f( 228, 228, 0 );
			 
				//Top-right vertex (corner)
				glTexCoord2i( 0, 1 );
				glVertex3f( 100, 228, 0 );
			glEnd();// Done Drawing The Quad
			SDL_GL_SwapBuffers();
		}
		


		
	}
}