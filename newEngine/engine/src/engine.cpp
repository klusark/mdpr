#include "engine.hpp"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

namespace engine{
	HGLRC			hRC=NULL;	// Permanent Rendering Context
	HDC				hDC=NULL;	// Private GDI Device Context
	HWND			hWnd=NULL;	// Holds Our Window Handle
	HINSTANCE		hInstance;	// Holds The Instance Of The Application

	EngineLib bool createWindow(int screenWidth, int screenHeight, int bitsPerPixel, const char * title)
	{
		//Initialize SDL
		if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
		{
			return false;    
		}

		//Create Window
		if( SDL_SetVideoMode(screenWidth, screenHeight, bitsPerPixel, SDL_OPENGL ) == NULL ){
			return false;
		}

		//Initialize OpenGL
		//if(init_GL() == false){
		//	return false;    
		//}
		glClearColor( 0, 0, 0, 0 ); 
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho( 0, screenWidth, screenHeight, 0, -1, 1 ); 
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity(); 
		if( glGetError() != GL_NO_ERROR ){
			return false;
		}

		//Set caption
		SDL_WM_SetCaption(title, NULL);

		return true;
	}
}