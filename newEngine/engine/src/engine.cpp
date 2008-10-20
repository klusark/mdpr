#include "engine.hpp"
#include <windows.h>	// Header File For Windows
#include <gl\gl.h>		// Header File For The OpenGL32 Library
#include <gl\glu.h>		// Header File For The GLu32 Library

namespace engine{
	namespace window{
		HGLRC			hRC=NULL;			// Permanent Rendering Context
		HDC				hDC=NULL;			// Private GDI Device Context
		HWND			hWnd=NULL;			// Holds Our Window Handle
		HINSTANCE		hInstance;			// Holds The Instance Of The Application
		bool			active=TRUE;		// Window Active Flag Set To TRUE By Default
		bool			fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default


		EngineLib bool createWindow(int screenWidth, int screenHeight, int bitsPerPixel, const char * title)
		{
			return true;
		}
	}

	namespace events{
		bool keys[256]; // Array Used For The Keyboard Routine
	}
}