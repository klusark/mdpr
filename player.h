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

		struct animation
		{
			short numFrames;
			SDL_Surface* frames[4];
			Uint32 delay;
			
		};
		bool rightPress;
		bool leftPress;
		short WALKSPEED;
		short velocityX;

		//animaitons
		animation run;
		
};
#endif
