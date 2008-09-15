#include <SDL.h>
#include "video.hpp"
#include "level.hpp"


/*
* init the level
*/
void Level::init()
{
	//init the platforms
	platform();

	//init the ropes
	rope();

	//init the edges
	edge();

	//emitters;
	emitter[0].x = 155;
	emitter[0].y = 0;
}

/*
* draw the level
*/
void Level::update()
{
	//draw the platforms
	for (short i = 0; i < 16; i++){
		SDL_BlitSurface(video::images[video::platform], &video::images[video::platform]->clip_rect, video::screen, &Level::platforms[i]);
		Level::platforms[i].h = 1;
	}
	//draw the ropes
	//TODO
	SDL_FillRect(video::screen, &ropes[0], SDL_MapRGB(video::screen->format, 144, 96, 0)); 
	SDL_Rect ropeRect;
	ropeRect.x = ropes[0].x - 2;
	ropeRect.y = ropes[0].y - 5;
	SDL_BlitSurface(video::images[video::ropetop], &video::images[video::ropetop]->clip_rect, video::screen, &ropeRect);

	//draw the emitters
	//TODO get more emitters
	SDL_BlitSurface(video::images[video::emitter], &video::images[video::emitter]->clip_rect, video::screen, &emitter[0]);
}

/*
* setup the ropes
*/
void Level::rope()
{
	ropes[0].x = 80 * video::scale;
	ropes[0].y = 19 * video::scale;
	ropes[0].w = 1 * video::scale;
	ropes[0].h = 150 * video::scale;
	
}

/*
* setup the platforms
*/
void Level::platform()
{
	short yTemp, xTemp;
	short i;

	//bottom left
	yTemp = 168 * video::scale;
	xTemp = 25 * video::scale;
	for (i = 0; i<=3; i++){
		Level::platforms[i].x = xTemp;
		Level::platforms[i].y = yTemp;
		xTemp += 16 * video::scale;
	}
	
	//bottom right
	xTemp = 233 * video::scale;
	for (i = 4; i<=7; i++){
		Level::platforms[i].x = xTemp;
		Level::platforms[i].y = yTemp;
		xTemp += 16 * video::scale;
	}


	//top left
	yTemp = 40 * video::scale;
	xTemp = 49 * video::scale;
	for (i = 8; i<=11; i++){
		Level::platforms[i].x = xTemp;
		Level::platforms[i].y = yTemp;
		xTemp += 16 * video::scale;
	}

	//top right
	xTemp = 209 * video::scale;
	for (i = 12; i<=15; i++){
		Level::platforms[i].x = xTemp;
		Level::platforms[i].y = yTemp;
		xTemp += 16 * video::scale;
	}
}

/*
* set up the edges
*/
void Level::edge()
{
	
	edgeLeft.x = 0;
	edgeLeft.y = 0;
	edgeLeft.w = 1;
	edgeLeft.h = video::height;

	edgeRight.x = video::width - 1;
	edgeRight.y = 0;
	edgeRight.w = 1;
	edgeRight.h = video::width;

	edgeTop.x = 0;
	edgeTop.y = 0;
	edgeTop.w = video::width + 1;
	edgeTop.h = 1;

	edgeBottom.x = 0;
	edgeBottom.y = video::height - 1;
	edgeBottom.w = video::width;
	edgeBottom.h = 1;
}

