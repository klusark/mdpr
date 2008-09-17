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
		
		short currentWeapon;

		struct animation
		{
			char numFrames, repeat, holdEnd, type;
			short xOffset, yOffset;
			SDL_Surface *frames[8];
			Uint32 delay;
			SDL_Rect animationRect;
			
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

		Uint32 lastTime, lastTimeX, lastTimeY, lastTimeGrav;

};
#endif
