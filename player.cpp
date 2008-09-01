#include "player.hpp"

//player::init
//sets up the player
//Parameters: None
//Return: None
void player::init()
{
	registerAnimations();
    currentFrame = 0;
    lastTime = 0;
	currAnimation = idle;
	rect.x = 50;
	rect.y = 50;
	rect.h = 24;
	rect.w = 24;
	walkspeed = 32;
	gravity = 8;
	velocityX = 0;
	

	//keys
	up = SDLK_UP;
	down = SDLK_DOWN;
	right = SDLK_RIGHT;
	left = SDLK_LEFT;

}

//player::input
//handles all the keyboard input for the player
//Parameters: None
//Return: None
void player::input()
{
	Uint8 *keystate = SDL_GetKeyState(0);

	//pressing right
	if (keystate[right]){
		if (!rightPress){
			lastTimeX = SDL_GetTicks();
			rightPress = true;
			currentFrame = 0;
		}
	}else{
		if (rightPress){
			rightPress = false;
		}
	}
		
	//pressing left
	if (keystate[left]){
		if (!leftPress){
			lastTimeX = SDL_GetTicks();
			leftPress = true;
			currentFrame = 0;
		}
	}else{
		if (leftPress){
			leftPress = false;
		}
	}

	if (leftPress || rightPress){
		currAnimation = run;
	}else if(currAnimation.type == run.type){
		currAnimation = idle;
	}

	//pressing up
	if (keystate[up]){

	}

	//pressing down
	if (keystate[down]){
		if (!downPress){
			downPress = true;
			currAnimation = crouch;
			currentFrame = 0;
		}
	}else{
		if (downPress){ 
			currAnimation = crouchup;
			currentFrame = 0;
			downPress = false;
		}
	}

	if (rightPress && leftPress){
		lastTimeX = SDL_GetTicks();
	}

	//if (!rightPress && !leftPress && !downPress){
	//	currAnimation = idle;
	//}

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
	/*if (!game::checkCollision(rect, game::platforms[0])){
		yMove = velocityY * (SDL_GetTicks() - lastTimeY)/1000.0;
		if (yMove >= 1 || yMove <= -1){
			lastTimeY = SDL_GetTicks();
			rect.y += (Sint16)yMove;
		}
	}else{
	}*/
	velocityY = 8;

	animate(currAnimation);
	if (!image)
		image = video::images[video::stand];
	//render the player onto the screen
	SDL_BlitSurface(SDL_DisplayFormat(image), 0, video::screen, &rect);
	
}

//player::animate
//animates the player sprite
//Parameters: the current animation
//Return: None
void player::animate(animation currAnimation){
	if(currAnimation.delay < (SDL_GetTicks() - lastTime) )
	{
		image = currAnimation.frames[currentFrame];
		if (currAnimation.holdEnd){
			if (currentFrame != currAnimation.numFrames-1){
				currentFrame++;
			}
		}else{
			currentFrame++;
		}
		lastTime = SDL_GetTicks();
		
		//if we reached the end
		if(currentFrame >= currAnimation.numFrames){
			if (currAnimation.repeat){
				currentFrame = 0;
			}else{
				player::currAnimation = idle;
				currentFrame = 0;
				return;
			}
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
	run.type = runType;
	run.numFrames = 4;
	run.delay = 100;
	run.repeat = 1;
	run.frames[0] = video::images[video::run0];
	run.frames[1] = video::images[video::run1];
	run.frames[2] = video::images[video::run2];
	run.frames[3] = video::images[video::run3];
	
	//upjump
	upjump.numFrames = 5;
	upjump.delay = 100;
	upjump.repeat = 0;
	upjump.frames[0] = video::images[video::upjump0];
	upjump.frames[1] = video::images[video::upjump1];
	upjump.frames[2] = video::images[video::upjump2];
	upjump.frames[3] = video::images[video::upjump3];
	upjump.frames[4] = video::images[video::upjump4];

	//crouch
	crouch.numFrames = 2;
	crouch.delay = 100;
	crouch.repeat = 0;
	crouch.holdEnd = 1;
	crouch.frames[0] = video::images[video::crouch0];
	crouch.frames[1] = video::images[video::crouch1];

	crouchup.numFrames = 2;
	crouchup.delay = 100;
	crouchup.repeat = 0;
	crouchup.frames[0] = video::images[video::crouch1];
	crouchup.frames[1] = video::images[video::crouch0];

	//idle
	idle.type = idleType;
	idle.numFrames = 1;
	idle.delay = 100;
	idle.repeat = 1;
	idle.frames[0] = video::images[video::stand];
}
