#ifndef bubble_h
#define bubble_h

class bubble
{
	
	public:
		void update();
		void init();

	private:
		SDL_Rect rect;
		SDL_Surface *images[4];
		char currentFrame;
		double xMove, yMove, velocityX, velocityY;
		Uint32 lastTime, lastTimeX, lastTimeY;
		int randomNum;

};

#endif
