#include <SDL.h>

#include "main.hpp"
#include "video.hpp"
#include "level.hpp"
#include "game.hpp"
#include "bubble.hpp"

/*
* update the bubble every frame
*/
void bubble::update()
{
	video::clear(rect);
	//if the bubble is not hidden
	if (!hide){
		
		//animate
		if(100 < (SDL_GetTicks() - lastTime) ){
			lastTime = SDL_GetTicks();
			currentFrame++;
			if (currentFrame >= 3)
				currentFrame = 0;
		}

		//move on the x
		moveX();

		//move on the y
		moveY();

		SDL_Surface *newImage = SDL_ConvertSurface(images[currentFrame], images[currentFrame]->format, images[currentFrame]->flags);

		//SDL_BlitSurface(images[currentFrame], 0, newImage, 0);

		SDL_BlitSurface(weaponImages[currentWeapon], 0, newImage, 0);

		//show the image
		video::addImageQueue(newImage, rect);
		//SDL_BlitSurface(newImage, 0, video::screen, &rect);

		//No leaks
		SDL_FreeSurface(newImage);

	}else{
		//do stuff when hiden

		//get the timers going
		lastTime = SDL_GetTicks();
		lastTimeX = SDL_GetTicks();
		lastTimeY = SDL_GetTicks();

		//get a radom new weapon
		currentWeapon = rand() % 9;

		//get a radom posiiton
		randomNum = rand()%3;
		if (randomNum == 0){
			rect.x = 155 * video::scale;
			rect.y = 5 * video::scale;
		}else if (randomNum == 1){
			rect.x = 5 * video::scale;
			rect.y = 95 * video::scale;
		}else if (randomNum == 2){
			rect.x = 315 * video::scale;
			rect.y = 95 * video::scale;
		}

		//get a radom velocity
		velocityX = (rand() % 25 + 45) * video::scale;
		velocityY = (rand() % 25 + 45) * video::scale;

		//make the bubble go down some times
		if (rand() % 2)
			velocityY = -velocityY;

		//make the bubble do to the side some times
		if (rand() % 2)
			velocityX = -velocityX;

		currentFrame = 0;
		
		hide = false;
		
	}
}

/*
* hide the bubble when it colides with the player
*/
void bubble::collided()
{

	//hide the bubble
	hide = true;

	//TODO display poping animation

}

/*
* init the bubble
*/
void bubble::init()
{
	images[0] = video::images[video::bubble0];
	images[1] = video::images[video::bubble1];
	images[2] = video::images[video::bubble2];

	rect.w = 16 * video::scale;
	rect.h = 16 * video::scale;

	//weapon images
	weaponImages[game.tenthousandvolts] =	video::images[video::tenthousandvolts];
	weaponImages[game.boot] =				video::images[video::boot];
	weaponImages[game.death] =				video::images[video::death];
	weaponImages[game.gun] =				video::images[video::gun];
	weaponImages[game.mine] =				video::images[video::mine];
	weaponImages[game.invis] =				video::images[video::invis];
	weaponImages[game.x] =					video::images[video::x];
	weaponImages[game.nade] =				video::images[video::nade];
	weaponImages[game.nuke] =				video::images[video::nuke];
	weaponImages[game.parachute] =			video::images[video::parachute];
	hide = true;
	
}

/*
* move the bubble on the X axis
*/
void bubble::moveX()
{
	xMove = velocityX * (SDL_GetTicks() - lastTimeX)/1000.0;
	//if going right
	if (xMove >= 1){
		lastTimeX = SDL_GetTicks();
		for (int i = 0; i <= xMove; i++){
			rect.x += 1;
			if (game.checkCollision(rect, game.level.edgeRight)){
				velocityX = -velocityX;
				break;
			}
		}
	//if going left
	}else if (xMove <= -1){
		lastTimeX = SDL_GetTicks();
		for (int i = 0; i >= xMove; i--){
			rect.x -= 1;
			if (game.checkCollision(rect, game.level.edgeLeft)){
				velocityX = -velocityX;
				break;
			}
		}
	}
}

/*
* move the bubble on the Y axis
*/
void bubble::moveY()
{
	yMove = velocityY * (SDL_GetTicks() - lastTimeY)/1000.0;
	//if going down
	if (yMove >= 1){
		lastTimeY = SDL_GetTicks();
		for (int i = 0; i <= yMove; i++){
			rect.y += 1;
			if (game.checkCollision(rect, game.level.edgeBottom)){
				velocityY = -velocityY;
				break;
			}
		}
	//if going up
	}else if (yMove <= -1){
		lastTimeY = SDL_GetTicks();
		for (int i = 0; i >= yMove; i--){
			rect.y -= 1;
			if (game.checkCollision(rect, game.level.edgeTop)){
				velocityY = -velocityY;
				break;
			}
		}
	}
}
