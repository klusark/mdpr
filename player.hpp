#ifndef player_h
#define player_h

#include "video.hpp"

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
		SDL_Rect rect2;
		SDL_Rect rect;
		short currentFrame;
		Uint32 lastTime;
		Uint32 lastTime2;
		SDL_Surface *image;
		SDL_Surface *stand;

		bool rightPress;
		bool leftPress;
		double xMove;

		short WALKSPEED;
		double velocityX;

		//animaitons
		animation currAnimation;
		animation noAnimation;
		animation run;
		animation upjump;
		
};
#endif
