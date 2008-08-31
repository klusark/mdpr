#include "video.hpp"

namespace video
{
	SDL_Surface *screen;
	SDL_Surface *images[numImages];

	//video::init
	//initializes the window for the program
	//Parameters: None
	//Return: None
	void init()
	{
		SDL_Init(SDL_INIT_VIDEO);

		//Make a window 640 by 480 with 32bit colour, hardware acceleration and double buffering
		SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE |SDL_HWACCEL | SDL_DOUBLEBUF);

		SDL_WM_SetCaption("Marshmallow Duel: Percy's Return", "Marshmallow Duel: Percy's Return");

		screen = SDL_GetVideoSurface();

		loadAll();
		return;
	}

	//video::loadAll
	//loads all the images used in the game
	//TODO! find a better way to load the images.
	//Parameters: None
	//Return: None
	void loadAll()
	{
		//player
		loadImage("stand", stand);

		loadImage("run0", run0);
		loadImage("run1", run1);
		loadImage("run2", run2);
		loadImage("run3", run3);

		loadImage("crouch0", crouch0);
		loadImage("crouch1", crouch1);

		loadImage("upjump0", upjump0);
		loadImage("upjump1", upjump1);
		loadImage("upjump2", upjump2);
		loadImage("upjump3", upjump3);
		loadImage("upjump4", upjump4);
		
		//world
		loadImage("platform", platform);

		return;
	}

	//video::loadImage
	//loads a png image from the data folder
	//Parameters: file name with out .png, the image number from the imageList enum
	//Return: Bool Success/Failure
	bool loadImage(char* file, short code)
	{
		SDL_RWops *rwop;
		char files[32];

		sprintf(files, "data/%s.png", file);
		rwop = SDL_RWFromFile(files, "rb");
		images[code] = IMG_LoadPNG_RW(rwop);

		//check for errors
		if(!images[code]){
			printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
			return false;
		}
		return true;
	}

	//video::switchBuf
	//switches the buffer. For compadibility for future porting
	//Parameters: None
	//Return: None
	void switchBuf()
	{
		SDL_Flip(screen);
		return;
	}
};
