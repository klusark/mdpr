#ifndef video_h
#define video_h

namespace video
{
	extern void init();
	extern bool loadImage(char* file, short code);
	extern void loadAll();
	extern void switchBuf();
	extern void limitFPS(short FPS);
	extern void clear(SDL_Rect rect);
	extern void addImageQueue(SDL_Surface *image, SDL_Rect rect);
	extern void blitImageQueue();


	enum imageList
	{	
		//player images
		stand,

		run0,
		run1,
		run2,
		run3,

		crouch0,
		crouch1,

		roll0,
		roll1,
		roll2,
		roll3,
		
		upjump0,
		upjump1,
		upjump2,
		upjump3,
		upjump4,

		//bubble
		bubble0,
		bubble1,
		bubble2,

		//weapons
		tenthousandvolts,
		boot,
		death,
		gun,
		mine,
		invis,
		x,
		nade,
		nuke,
		parachute,

		//effects
		bubblepop0,
		bubblepop1,

		bubblestart0,
		bubblestart1,
		bubblestart2,

		//world
		platform,

		emitter,

		//total number of images
		numImages,
	};

	extern SDL_Surface *screen, *images[numImages];

}
#endif
