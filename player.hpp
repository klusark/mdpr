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
			char numFrames, repeat, holdEnd, type;
			SDL_Surface *frames[8];
			Uint32 delay;
			
		};
		void animate(animation currAnimation);
		void registerAnimations();
		
		

		SDL_Rect rect;

		Uint32 lastTime, lastTimeX, lastTimeY;

		SDL_Surface *image;

		bool rightPress, leftPress, downPress, upPress;

		double xMove, yMove, velocityX, velocityY;

		short walkspeed, gravity, currentFrame;
		//keys
		short up, down, right, left;
		//animaitons
		animation currAnimation, idle, run, upjump, crouch, crouchup;

		enum animationTypes{
			idleType,
			runType,
			upjumpType,
			crouchType,
			crouchupType,
		};
		
};
#endif
