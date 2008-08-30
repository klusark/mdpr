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
	{	//player images
		stand,

		run0,
		run1,
		run2,
		run3,

		crouch0,
		crouch1,
		
		upjump0,
		upjump1,
		upjump2,
		upjump3,
		upjump4,

		numImages,//total number of images
	};
	extern SDL_Surface *screen;
	extern SDL_Surface* images[numImages];

}
#endif
