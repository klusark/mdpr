#ifndef main_h
#define main_h
#include <stdlib.h>
//#include <SDL.h>

#include "video.hpp"
#include "game.hpp"
#include "menu.hpp"
//#include "player.h"


enum States
{
	inMenu,
	inGame,
};
extern void mainLoop();
extern short currState;
extern bool running;

#endif
