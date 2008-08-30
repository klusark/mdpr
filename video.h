#ifndef video_h
#define video_h
#include <SDL.h>
#include <SDL_image.h>

namespace video
{
	extern void init();
	extern bool loadImage(char* file, short code);
	extern void loadAll();
	extern void switchBuf();

	extern enum imageList
	{
		stand,
		run0,
		run1,
		run2,
		run3,
		numImages,
	};
	extern SDL_Surface *screen;
	extern SDL_Surface* images[numImages];
}
#endif
