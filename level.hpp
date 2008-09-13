#ifndef level_h
#define level_h

class Level
{
	public:
		void init();
		void update();
		void platform();
		void rope();
		void edge();
		SDL_Rect platforms[16], edgeTop, edgeLeft, edgeBottom, edgeRight, emitter[3], ropes[4];

};

#endif
