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
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 ); // *new*
			 
			SDL_SetVideoMode( 640, 480, 32, SDL_OPENGL);

			glEnable( GL_TEXTURE_2D );
 
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			 
			glViewport( 0, 0, 640, 480 );
			 
			glClear( GL_COLOR_BUFFER_BIT );
			 
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			 
			glOrtho(0.0f, 640, 480, 0.0f, -1.0f, 1.0f);
			 
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();

			return true;
		}

		EngineLib void eventLoop()
		{
			SDL_Event events;
			while (SDL_PollEvent(&events)){
				if (events.type == SDL_QUIT){
					//quit the game
					throw 1; 
				}
			}
		}

		EngineLib void mainLoop()
		{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle
	glTranslatef(3.0f,0.0f,0.0f);						// Move Right 3 Units
	glBegin(GL_QUADS);									// Draw A Quad
		glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
		glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glEnd();											// Done Drawing The Quad
	SDL_GL_SwapBuffers();
		}
		


		
	}
}