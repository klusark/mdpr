#ifndef bubble_h
#define bubble_h

class bubble
{
	
	public:
		void update();
		void init();

	private:
		void moveX();
		void moveY();
		SDL_Rect rect;
		SDL_Surface *images[3];
		char currentFrame, currentWeapon;
		double xMove, yMove, velocityX, velocityY;
		Uint32 lastTime, lastTimeX, lastTimeY;
		int randomNum;
		SDL_Surface *weaponImages[10];

};

#endif
