#include <SDL.h>
#include <SDL_image.h>

#include "main.hpp"
#include "video.hpp"

namespace video
{
	SDL_Surface *screen, *images[numImages];
	Uint32 bticks, cticks;
	short width, height;

	struct queue
	{
		SDL_Surface *image;
		SDL_Rect rect;
	}imageQueue[5];
	short queueSize = 0;
	//video::init
	//initializes the window for the program
	//Parameters: None
	//Return: None
	void init()
	{
		SDL_Init(SDL_INIT_VIDEO);

		//Make a window 320 by 200 with 32bit colour, hardware acceleration and double buffering
		width = 320;
		height = 200;
		screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE |SDL_HWACCEL | SDL_DOUBLEBUF);

		SDL_WM_SetCaption("Marshmallow Duel: Percy's Return", "Marshmallow Duel: Percy's Return");

		//load all the images
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

		loadImage("roll0", roll0);
		loadImage("roll1", roll1);
		loadImage("roll2", roll2);
		loadImage("roll3", roll3);

		loadImage("upjump0", upjump0);
		loadImage("upjump1", upjump1);
		loadImage("upjump2", upjump2);
		loadImage("upjump3", upjump3);
		loadImage("upjump4", upjump4);
		
		//bubble
		loadImage("bubble0", bubble0);
		loadImage("bubble1", bubble1);
		loadImage("bubble2", bubble2);

		//powerups
		loadImage("tenthousandvolts", tenthousandvolts);
		loadImage("boot", boot);
		loadImage("death", death);
		loadImage("gun", gun);
		loadImage("mine", mine);
		loadImage("invis", invis);
		loadImage("x", x);
		loadImage("nade", nade);
		loadImage("nuke", nuke);
		loadImage("parachute", parachute);
		
		//world
		loadImage("platform", platform);

		loadImage("emitter", emitter);

		loadImage("ropetop", ropetop);

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

		sprintf(files, "data/%s/%s.png", theme, file);
		rwop = SDL_RWFromFile(files, "rb");
		images[code] = IMG_LoadPNG_RW(rwop);

		//check for errors
		if(!images[code]){
			sprintf(files, "data/%s/%s.png", "main", file);
			rwop = SDL_RWFromFile(files, "rb");
			images[code] = IMG_LoadPNG_RW(rwop);
			if(!images[code]){
				printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
				return false;
			}
		}
		return true;
	}

	//video::limitFPS
	//Limit the frames per second to FPS
	//Parameters: FPS the max frames per second
	//Return: None
	void limitFPS(short FPS)
	{
		Uint32 wait = (Uint32)(1000 / FPS);

		cticks = SDL_GetTicks();
		if ((cticks - bticks) < wait){
			//framerate exceeded limit....so we wait the difference
			SDL_Delay(wait - (cticks - bticks));
		}
		bticks = SDL_GetTicks();
	}

	//video::switchBuf
	//switches the buffer. For compadibility for future porting
	//Parameters: None
	//Return: None
	void switchBuf()
	{
		SDL_Flip(screen);
	}

	void clear(SDL_Rect rect)
	{
		SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0)); 
	}
	
	void addImageQueue(SDL_Surface *image, SDL_Rect rect)
	{
		imageQueue[queueSize].image = SDL_ConvertSurface(image, image->format, image->flags);
		imageQueue[queueSize].rect = rect;
		queueSize++;
	}

	void blitImageQueue()
	{
		for (short i = 0; i < queueSize; i++){
			SDL_BlitSurface(imageQueue[i].image, 0, video::screen, &imageQueue[i].rect);
			SDL_FreeSurface(imageQueue[i].image);
		}
		queueSize = 0;
	}
};
