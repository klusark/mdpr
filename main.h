#ifndef main_h
#define main_h
#include <stdlib.h>
//#include <SDL.h>

#include "video.h"
#include "game.h"
#include "menu.h"
//#include "player.h"


enum States
{
	inMenu,
	inGame,
};
extern short currState;
extern bool running;

#endif
