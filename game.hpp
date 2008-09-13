#ifndef game_h
#define game_h

#include "bubble.hpp"
#include "player.hpp"

class game
{
	public:
		void mainLoop();
		void init();
		bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
		bubble bubbles[3];
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
		player player1;
		player player2;



		Uint32 lastTime;
		unsigned int shownFrames;
};

#endif
