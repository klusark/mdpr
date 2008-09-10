#include <SDL.h>
#include "video.hpp"
#include "level.hpp"

namespace level
{
	SDL_Rect platforms[16], edgeTop, edgeLeft, edgeBottom, edgeRight;
	void init()
	{
		//bottom left
		level::platforms[0].x = 25;
		level::platforms[0].y = 168;

		level::platforms[1].x = 41;
		level::platforms[1].y = 168;

		level::platforms[2].x = 57;
		level::platforms[2].y = 168;

		level::platforms[3].x = 73;
		level::platforms[3].y = 168;

		//bottom right
		level::platforms[4].x = 233;
		level::platforms[4].y = 168;

		level::platforms[5].x = 249;
		level::platforms[5].y = 168;

		level::platforms[6].x = 265;
		level::platforms[6].y = 168;

		level::platforms[7].x = 281;
		level::platforms[7].y = 168;

		//top left
		level::platforms[8].x = 49;
		level::platforms[8].y = 40;

		level::platforms[9].x = 65;
		level::platforms[9].y = 40;

		level::platforms[10].x = 81;
		level::platforms[10].y = 40;

		level::platforms[11].x = 97;
		level::platforms[11].y = 40;

		//top right
		level::platforms[12].x = 209;
		level::platforms[12].y = 40;

		level::platforms[13].x = 225;
		level::platforms[13].y = 40;

		level::platforms[14].x = 241;
		level::platforms[14].y = 40;

		level::platforms[15].x = 257;
		level::platforms[15].y = 40;

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
		edgeBottom.y = 239;
		edgeBottom.w = 320;
		edgeBottom.h = 1;

	}

	void update()
	{
		for (char i = 0; i < 16; i++){
			SDL_BlitSurface(video::images[video::platform], &video::images[video::platform]->clip_rect, video::screen, &level::platforms[i]);
			level::platforms[i].h = 1;
		}
	}
}
