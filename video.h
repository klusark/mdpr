#ifndef video_h
#define video_h
#include <SDL.h>
#include <SDL_image.h>

namespace video
{
	extern bool init();
	extern bool loadImage(char* file, short code);
	extern bool loadAll();

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
