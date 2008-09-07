#ifndef game_h
#define game_h

#include "main.hpp"
#include "player.hpp"
#include "video.hpp"
#include "bubble.hpp"
#include "level.hpp"

namespace game
{
	extern void mainLoop();
	extern void init();
	extern bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);

}

#endif
