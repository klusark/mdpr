#ifndef player_h
#define player_h

//#include "main.h"
#include "video.h"
class player
{
	public:
		void init();
		void update();
		void input();
		SDL_Rect rect2;
		short currentFrame;
		Uint32 lastTime;
		Uint32 lastTime2;
		struct animation
		{
			short numFrames;
			SDL_Surface* frames[4];
			Uint32 delay;
			
		};
		bool rightPress;
		bool leftPress;
		double temp;

		short WALKSPEED;
		double velocityX;

		//animaitons
		animation run;
		
};
#endif
