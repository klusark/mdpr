#include "player.h"

void player::init()
{
    currentFrame = 0;
    lastTime = SDL_GetTicks();
	stand = video::images[video::stand];
	currAnimation = noAnimation;
	rect.x = 50;
	rect.y = 50;
	rect.h = 24;
	rect.w = 24;
	run.numFrames = 4;
	run.delay = 100;
	WALKSPEED = 32;
	velocityX = 0;
	image = stand;
	run.frames[0] = video::images[video::run0];
	run.frames[1] = video::images[video::run1];
	run.frames[2] = video::images[video::run2];
	run.frames[3] = video::images[video::run3];
	return;
}

void player::input()
{
	Uint8 *keystate = SDL_GetKeyState(0);
	if ( keystate[SDLK_RIGHT] ){
		if (!rightPress){
			lastTime2 = SDL_GetTicks();
			rightPress = true;
			currAnimation = run;
		}
	}else
		rightPress = false;
		

	if ( keystate[SDLK_LEFT] ){
		if (!leftPress){
			lastTime2 = SDL_GetTicks();
			leftPress = true;
			currAnimation = run;
		}
	}else
		leftPress = false;

	if (rightPress && leftPress){
		lastTime2 = SDL_GetTicks();
	}

	if (!rightPress && !leftPress){
		currAnimation = noAnimation;
		image = stand;
	}

	velocityX = (rightPress - leftPress) * WALKSPEED;
	
}

void player::update()
{
	rect2 = rect;
	input();
	xMove = velocityX * (SDL_GetTicks() - lastTime2)/1000.0;
	if (xMove >= 1 || xMove <= -1){
		lastTime2 = SDL_GetTicks();
		rect2.x += (Sint16)xMove;
	}
	animate(currAnimation);

	SDL_FillRect(video::screen, &rect, 0);//gets rid of old image
	SDL_BlitSurface(image, 0, video::screen, &rect2);
	rect = rect2;
	
}

void player::animate(animation currAnimation){
	if (currAnimation.numFrames){//check if set as noAnimation
		if(currAnimation.delay < (SDL_GetTicks() - lastTime) )
		{
			currentFrame++;
			lastTime = SDL_GetTicks();
			
			//if we reached the end
			if(currentFrame >= currAnimation.numFrames)
			{
				currentFrame = 0;
			}
			rect.x -= 1; //otherwise there are left over pixels
			image = currAnimation.frames[currentFrame];
		}
	}
}
