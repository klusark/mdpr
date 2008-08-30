#include "video.h"
namespace video
{
	enum imageList;
	SDL_Surface *screen;
	SDL_Surface *images[numImages];
	bool video::init()
	{
		SDL_Init(SDL_INIT_VIDEO);

		SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE |SDL_HWACCEL | SDL_DOUBLEBUF);

		SDL_WM_SetCaption("Marshmallow Duel: Percy's Return", "Marshmallow Duel: Percy's Return");

		screen = SDL_GetVideoSurface();

		loadAll();
		return true;
	}

	bool video::loadAll()
	{
		loadImage("stand", stand);
		loadImage("run0", run0);
		loadImage("run1", run1);
		loadImage("run2", run2);
		loadImage("run3", run3);
		return true;
	}

	bool video::loadImage(char* file, short code)
	{

		// load sample.png into image
		video::images[code];
		SDL_RWops *rwop;
		char files[32];
		sprintf(files, "data/%s.png", file);
		rwop = SDL_RWFromFile(files, "rb");
		video::images[code] = IMG_LoadPNG_RW(rwop);
		if(!video::images[code]){
			printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
			return false;
		}
		SDL_SetColorKey(video::images[code], SDL_SRCCOLORKEY, 0);
		return true;
	}
};