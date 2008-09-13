#ifndef player_h
#define player_h

class player
{
	public:
		void init(char);
		void update();
			
	private:
		void animate();
		void input();
		void registerAnimations();
		void moveY();
		void moveX();
		void collide();

		struct animation
		{
			char numFrames, repeat, holdEnd, type;
			SDL_Surface *frames[8];
			Uint32 delay;
			
		}currAnimation, idle, run, upjump, crouch, crouchup, roll;

		SDL_Surface *image;

		bool rightPress, leftPress, downPress, upPress, onGround;

		double xMove, yMove, velocityX, velocityY, leftOverX;

		char playerNumber;

		short walkspeed, maxVelocityY, currentFrame;
		//keys
		short up, down, right, left;

		enum animationTypes{
			idleType,
			runType,
			upjumpType,
			crouchType,
			crouchupType,
			rollType,
		};

		SDL_Rect rect, feetRect;

		Uint32 lastTime, lastTimeX, lastTimeY;

};
#endif
