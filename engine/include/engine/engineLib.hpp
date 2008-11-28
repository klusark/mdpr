#ifndef engineLib_hpp
#define engineLib_hpp

#if defined(_WIN32) || defined(WIN32)
#define EngineLib __declspec( dllexport )
#endif
#if defined(__linux__)
#define EngineLib
#endif

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#endif