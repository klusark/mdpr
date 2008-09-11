#ifndef game_h
#define game_h

namespace game
{
	extern void mainLoop();
	extern void init();
	extern bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
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
