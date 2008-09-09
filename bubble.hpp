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
		char currentFrame, xMove, yMove;
		Uint32 lastTime;
		int randomNum;

};

#endif
