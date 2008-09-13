#include <SDL.h>

#include "main.hpp"
#include "video.hpp"
#include "game.hpp"
#include "level.hpp"
#include "player.hpp"

//player::update
//does all the per-frame actions.
//Parameters: None
//Return: None
void player::update()
{
	//get keyboard input
	input();

	//todo put this in a funtion
	feetRect.x = rect.x + 7;
	rect.y = feetRect.y - (rect.h - feetRect.h);

	//move on the X
	moveX();

	//make the player fall
	moveY();

	//animate the player
	animate();
	
	//collide with the other player and the bubbles
	collide();
	
	//make sure that image is set
	if (!image)
		image = video::images[video::stand];

	//drawn the player onto the screen
	SDL_BlitSurface(this->image, 0, video::screen, &rect);
	 
}

//player::collide
//handles all the collsions other than with platforms
//Parameters: None
//Return: None
void player::collide()
{
	//colliding with a bubble
	for (char i = 0; i<3; i++){
		if (Game.checkCollision(rect, Game.bubbles[i].rect)){
			Game.bubbles[i].collided();
		}
	}
}

//player::init
//sets up the player
//Parameters: None
//Return: None
void player::init(char playerNumber)
{
	this->playerNumber = playerNumber;
	image = video::images[video::stand];
	registerAnimations();
    currentFrame = 0;
    lastTime = 0;
	this->currAnimation = idle;
	rect.x = 50;
	rect.y = 50;
	rect.h = 24;
	rect.w = 24;
	feetRect.h = 1;
	feetRect.w = rect.w - (6 + 7); // 7 for the right side 6 for the left
	feetRect.y = rect.y + (rect.h - feetRect.h);
	feetRect.x = rect.x + 7;
	walkspeed = 32;
	maxVelocityY = 32;
	velocityX = 0;
	

	//keys
	if (this->playerNumber == 1){
		up = SDLK_UP;
		down = SDLK_DOWN;
		right = SDLK_RIGHT;
		left = SDLK_LEFT;
	}else if (this->playerNumber == 2){
		up = SDLK_w;
		down = SDLK_s;
		right = SDLK_d;
		left = SDLK_a;
	}

}

//player::input
//handles all the keyboard input for the player
//Parameters: None
//Return: None
void player::input()
{
	Uint8 *keystate = SDL_GetKeyState(0);
	//if touching the ground
	if (onGround){
		//if not crouching
		if (currAnimation.type != crouch.type && currAnimation.type != crouchup.type){
			//pressing right
			if (keystate[right]){
				if (!rightPress){
					lastTimeX = SDL_GetTicks();
					rightPress = true;
					currentFrame = 0;
				}
				if (keystate[down]){
					currAnimation = roll;
					downPress = true;
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
				if (keystate[down]){
					currAnimation = roll;
					downPress = true;
				}
			}else{
				if (leftPress){
					leftPress = false;
				}
			}
			velocityX = (rightPress - leftPress) * walkspeed;
		}else{
			lastTimeX = SDL_GetTicks();
			velocityX = 0;
		}

		if (leftPress || rightPress && currAnimation.type != roll.type && currAnimation.type != crouch.type){
			currAnimation = run;
		}else if(currAnimation.type == run.type){
			currAnimation = idle;
		}

		//pressing up
		if (keystate[up]){
			if (!upPress){
				upPress = true;
				currAnimation = upjump;
				currentFrame = 0;
				velocityY = -16;
			}
		}

		if (currAnimation.type != run.type){
			//pressing down
			if (keystate[down]){
				if (!downPress){
					downPress = true;
					currAnimation = crouch;
					currentFrame = 0;
				}
			}else{
				if (downPress && currAnimation.type == crouchType){ 
					currAnimation = crouchup;
					currentFrame = 0;
					downPress = false;
				}
			}
		}

		if (rightPress && leftPress){
			lastTimeX = SDL_GetTicks();
		}
	}
}

//player::animate
//animates the player sprite
//Parameters: None
//Return: None
void player::animate()
{
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
				if (currAnimation.type == rollType){
					this->currAnimation = crouch;
				}else{
					this->currAnimation = idle;
				}
				currentFrame = 0;
				return;
			}
		}
	}
}

//player::moveX
//moves the player on the x axis
//Parameters: None
//Return: None
void player::moveX()
{
	xMove = velocityX * (SDL_GetTicks() - lastTimeX)/1000.0;
	if (xMove >= 1 || xMove <= -1){
		lastTimeX = SDL_GetTicks();
		rect.x += (Sint16)xMove;
	}
}

//player::moveY
//makes the player fall and colide with platforms
//Parameters: None
//Return: None
void player::moveY()
{
	if (velocityY < maxVelocityY){
		velocityY++;
	}
	onGround = false;
	bool breaks = false;

	yMove = velocityY * (SDL_GetTicks() - lastTimeY)/1000.0;
	if (yMove >= 1){
		lastTimeY = SDL_GetTicks();
		for (int i = 0; i <= yMove; i++){
			feetRect.y += 1;
			for (int x = 0; x < 16; x++){
				if (Game.checkCollision(feetRect, level::platforms[x])){
					feetRect.y -= 1;
					rect.y = feetRect.y - (rect.h - feetRect.h);
					breaks = true;
					onGround = true;
					break;

				}
			}
			if (breaks)
				break;
		}
	}else if (yMove <= -1){
		lastTimeY = SDL_GetTicks();
		for (int i = 0; i >= yMove; i--){
			feetRect.y -= 1;
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
	crouch.type = crouchType;
	crouch.numFrames = 2;
	crouch.delay = 100;
	crouch.repeat = 0;
	crouch.holdEnd = 1;
	crouch.frames[0] = video::images[video::crouch0];
	crouch.frames[1] = video::images[video::crouch1];

	crouchup.numFrames = 2;
	crouchup.type = crouchupType;
	crouchup.delay = 100;
	crouchup.repeat = 0;
	crouchup.frames[0] = video::images[video::crouch1];
	crouchup.frames[1] = video::images[video::crouch0];

	//roll
	roll.numFrames = 4;
	roll.type = rollType;
	roll.delay = 100;
	roll.repeat = 0;
	roll.frames[0] = video::images[video::roll0];
	roll.frames[1] = video::images[video::roll1];
	roll.frames[2] = video::images[video::roll2];
	roll.frames[3] = video::images[video::roll3];

	//idle
	idle.type = idleType;
	idle.numFrames = 1;
	idle.delay = 100;
	idle.repeat = 1;
	idle.frames[0] = video::images[video::stand];
}
