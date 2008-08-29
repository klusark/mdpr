#include "player.h"

void player::init()
{
    currentFrame = 0;
    lastTime = SDL_GetTicks();
	rect2.x = 50;
	rect2.y = 50;
	rect2.h = 24;
	rect2.w = 24;
	run.numFrames = 4;
	run.delay = 100;
	WALKSPEED = 1;
	velocityX = 0;
	run.frames[0] = video::images[video::run0];
	run.frames[1] = video::images[video::run1];
	run.frames[2] = video::images[video::run2];
	run.frames[3] = video::images[video::run3];
	return;
}

void player::input()
{
	Uint8 *keystate = SDL_GetKeyState(0);
	if ( keystate[SDLK_RIGHT] ) 
		rightPress = true;
	else
		rightPress = false;
	if ( keystate[SDLK_LEFT] ) 
		leftPress = true;
	else
		leftPress = false;
	velocityX = (rightPress - leftPress) * WALKSPEED;	
}

void player::update()
{
	input();
	rect2.x += velocityX;
	//find out if enough time has passed
	if( run.delay < (SDL_GetTicks() - lastTime) )
	{
		currentFrame++;
		lastTime = SDL_GetTicks();
		
		//if we reached the end
		if(currentFrame >= run.numFrames)
		{
			currentFrame = 0;
		}
		SDL_BlitSurface(run.frames[currentFrame], &run.frames[currentFrame]->clip_rect, video::screen, &rect2);
		SDL_Flip(video::screen);
	}
}
