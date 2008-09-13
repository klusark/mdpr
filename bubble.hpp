#ifndef bubble_h
#define bubble_h

class bubble
{
	public:
		void update();
		void init();
		void collided();
		SDL_Rect rect;
		bool hide;

	private:
		void moveX();
		void moveY();

		
		char currentFrame, currentWeapon, randomNum;
		double xMove, yMove, velocityX, velocityY;
		Uint32 lastTime, lastTimeX, lastTimeY;
		SDL_Surface *weaponImages[10], *images[3];

};

#endif
