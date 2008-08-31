#ifndef player_h
#define player_h

#include "video.hpp"
#include "game.hpp"

class player
{
	public:
		void init();
		void update();
		void input();
		struct animation
		{
			short numFrames;
			SDL_Surface *frames[4];
			Uint32 delay;
			
		};
		void animate(animation currAnimation);
		void registerAnimations();

		SDL_Rect rect;

		Uint32 lastTime, lastTimeX, lastTimeY;

		SDL_Surface *image, *stand;

		bool rightPress, leftPress;

		double xMove, yMove, velocityX, velocityY;

		short walkspeed, gravity, currentFrame;

		//animaitons
		animation currAnimation, noAnimation, run, upjump;
		
};
#endif
