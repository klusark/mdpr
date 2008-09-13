#include <SDL.h>
#include "video.hpp"
#include "level.hpp"

/*
* the level namespace
* TODO change this to a class
*/

//SDL_Rect platforms[16], edgeTop, edgeLeft, edgeBottom, edgeRight, emitter[3], ropes[4];

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
	for (char i = 0; i < 16; i++){
		SDL_BlitSurface(video::images[video::platform], &video::images[video::platform]->clip_rect, video::screen, &Level::platforms[i]);
		Level::platforms[i].h = 1;
	}
	//draw the ropes
	//TODO

	//draw the emitters
	//TODO get more emitters
	SDL_BlitSurface(video::images[video::emitter], &video::images[video::emitter]->clip_rect, video::screen, &emitter[0]);
}

/*
* setup the ropes
*/
void Level::rope()
{
	ropes[0].x = 80;
	ropes[0].y = 19;
}

/*
* setup the platforms
*/
void Level::platform()
{
	//bottom left
	Level::platforms[0].x = 25;
	Level::platforms[0].y = 168;

	Level::platforms[1].x = 41;
	Level::platforms[1].y = 168;

	Level::platforms[2].x = 57;
	Level::platforms[2].y = 168;

	Level::platforms[3].x = 73;
	Level::platforms[3].y = 168;

	//bottom right
	Level::platforms[4].x = 233;
	Level::platforms[4].y = 168;

	Level::platforms[5].x = 249;
	Level::platforms[5].y = 168;

	Level::platforms[6].x = 265;
	Level::platforms[6].y = 168;

	Level::platforms[7].x = 281;
	Level::platforms[7].y = 168;

	//top left
	Level::platforms[8].x = 49;
	Level::platforms[8].y = 40;

	Level::platforms[9].x = 65;
	Level::platforms[9].y = 40;

	Level::platforms[10].x = 81;
	Level::platforms[10].y = 40;

	Level::platforms[11].x = 97;
	Level::platforms[11].y = 40;

	//top right
	Level::platforms[12].x = 209;
	Level::platforms[12].y = 40;

	Level::platforms[13].x = 225;
	Level::platforms[13].y = 40;

	Level::platforms[14].x = 241;
	Level::platforms[14].y = 40;

	Level::platforms[15].x = 257;
	Level::platforms[15].y = 40;

}

/*
* set up the edges
*/
void Level::edge()
{
	
	edgeLeft.x = 0;
	edgeLeft.y = 0;
	edgeLeft.w = 1;
	edgeLeft.h = 320;

	edgeRight.x = 319;
	edgeRight.y = 0;
	edgeRight.w = 2;
	edgeRight.h = 320;

	edgeTop.x = 0;
	edgeTop.y = 0;
	edgeTop.w = 321;
	edgeTop.h = 1;

	edgeBottom.x = 0;
	edgeBottom.y = 199;
	edgeBottom.w = 320;
	edgeBottom.h = 1;
}

