#ifndef game_h
#define game_h

#include "main.hpp"
#include "player.hpp"
#include "video.hpp"

namespace game
{
	extern void mainLoop();
	extern void init();
	extern void drawPlatforms();
	extern bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
	extern SDL_Rect platforms[4];
	extern Uint32 cticks, bticks, wait;
}

#endif
