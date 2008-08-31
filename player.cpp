#include "player.hpp"

//player::init
//sets up the player
//Parameters: None
//Return: None
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
	walkspeed = 32;
	gravity = 8;
	velocityX = 0;
	registerAnimations();
	return;
}

//player::input
//handles all the keyboard input for the player
//Parameters: None
//Return: None
void player::input()
{
	Uint8 *keystate = SDL_GetKeyState(0);
	if ( keystate[SDLK_RIGHT] ){
		if (!rightPress){
			lastTimeX = SDL_GetTicks();
			rightPress = true;
			currAnimation = run;
		}
	}else{
		rightPress = false;
	}
		

	if ( keystate[SDLK_LEFT] ){
		if (!leftPress){
			lastTimeX = SDL_GetTicks();
			leftPress = true;
			currAnimation = run;
		}
	}else{
		leftPress = false;
	}

	if (rightPress && leftPress){
		lastTimeX = SDL_GetTicks();
	}

	if (!rightPress && !leftPress){
		currAnimation = noAnimation;
		image = stand;
	}

	velocityX = (rightPress - leftPress) * walkspeed;
	
}

//player::update
//does all the per-frame actions.
//Parameters: None
//Return: None
void player::update()
{
	
	input();

	//Moving on the X
	xMove = velocityX * (SDL_GetTicks() - lastTimeX)/1000.0;
	if (xMove >= 1 || xMove <= -1){
		lastTimeX = SDL_GetTicks();
		rect.x += (Sint16)xMove;
	}

	//gravity
	if (!game::checkCollision(rect, game::platforms[0])){
		yMove = velocityY * (SDL_GetTicks() - lastTimeY)/1000.0;
		if (yMove >= 1 || yMove <= -1){
			lastTimeY = SDL_GetTicks();
			rect.y += (Sint16)yMove;
		}
	}else{
	}
	velocityY = 8;

	animate(currAnimation);

	//render the player onto the screen
	SDL_BlitSurface(SDL_DisplayFormat(image), 0, video::screen, &rect);
	
}

//player::animate
//animates the player sprite
//Parameters: the current animation
//Return: None
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

			image = currAnimation.frames[currentFrame];
		}
	}
}

//player::registerAnimations
//gets all the animations for the player ready
//Parameters: None
//Return: None
void player::registerAnimations()
{	
	//run
	run.numFrames = 4;
	run.delay = 100;
	run.frames[0] = video::images[video::run0];
	run.frames[1] = video::images[video::run1];
	run.frames[2] = video::images[video::run2];
	run.frames[3] = video::images[video::run3];
	
	//upjump
	upjump.numFrames = 5;
	upjump.delay = 100;
	upjump.frames[0] = video::images[video::upjump0];
	upjump.frames[1] = video::images[video::upjump1];
	upjump.frames[2] = video::images[video::upjump2];
	upjump.frames[3] = video::images[video::upjump3];
	upjump.frames[4] = video::images[video::upjump4];
	return;
}
