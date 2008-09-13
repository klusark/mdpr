#ifndef game_h
#define game_h

#include "bubble.hpp"

namespace game
{
	extern void mainLoop();
	extern void init();
	extern bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
	extern bubble bubbles[3];
	enum weapons
	{
		tenthousandvolts,
		boot,
		death,
		gun,
		mine,
		invis,
		x,
		nade,
		nuke,
		parachute,
	};
}

#endif
