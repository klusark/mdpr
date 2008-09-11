#include <SDL.h>

#include "video.hpp"
#include "level.hpp"
#include "game.hpp"
#include "bubble.hpp"

void bubble::update()
{
	
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

	SDL_BlitSurface(images[currentFrame], 0, newImage, 0);

	SDL_BlitSurface(weaponImages[currentWeapon], 0, newImage, 0);

	//show the image
	SDL_BlitSurface(newImage, 0, video::screen, &rect);

}

void bubble::init()
{
	lastTime = SDL_GetTicks();
	lastTimeX = SDL_GetTicks();
	images[0] = video::images[video::bubble0];
	images[1] = video::images[video::bubble1];
	images[2] = video::images[video::bubble2];
	randomNum = rand()%3;
	if (randomNum == 0){
		rect.x = 100;
		rect.y = 100;
	}else if (randomNum == 1){
		rect.x = 50;
		rect.y = 50;
	}else if (randomNum == 2){
		rect.x = 150;
		rect.y = 150;
	}
	rect.w = 16;
	rect.h = 16;
	currentFrame = 0;
	velocityX = rand() % 30 + 30;
	velocityY = rand() % 30 + 30;

	//weapon images
	weaponImages[game::tenthousandvolts] =	video::images[video::tenthousandvolts];
	weaponImages[game::boot] =				video::images[video::boot];
	weaponImages[game::death] =				video::images[video::death];
	weaponImages[game::gun] =				video::images[video::gun];
	weaponImages[game::mine] =				video::images[video::mine];
	weaponImages[game::invis] =				video::images[video::invis];
	weaponImages[game::x] =					video::images[video::x];
	weaponImages[game::nade] =				video::images[video::nade];
	weaponImages[game::nuke] =				video::images[video::nuke];
	weaponImages[game::parachute] =			video::images[video::parachute];

	currentWeapon = rand() % 9;

}

void bubble::moveX()
{
	xMove = velocityX * (SDL_GetTicks() - lastTimeX)/1000.0;
	if (xMove >= 1){
		lastTimeX = SDL_GetTicks();
		for (int i = 0; i <= xMove; i++){
			rect.x += 1;
			if (game::checkCollision(rect, level::edgeRight)){
				velocityX = -velocityX;
				break;
			}
		}
	}else if (xMove <= -1){
		lastTimeX = SDL_GetTicks();
		for (int i = 0; i >= xMove; i--){
			rect.x -= 1;
			if (game::checkCollision(rect, level::edgeLeft)){
				velocityX = -velocityX;
				break;
			}
		}
	}
}

void bubble::moveY()
{
	yMove = velocityY * (SDL_GetTicks() - lastTimeY)/1000.0;
	if (yMove >= 1){
		lastTimeY = SDL_GetTicks();
		for (int i = 0; i <= yMove; i++){
			rect.y += 1;
			if (game::checkCollision(rect, level::edgeBottom)){
				velocityY = -velocityY;
				break;
			}
		}
	}else if (yMove <= -1){
		lastTimeY = SDL_GetTicks();
		for (int i = 0; i >= yMove; i--){
			rect.y -= 1;
			if (game::checkCollision(rect, level::edgeTop)){
				velocityY = -velocityY;
				break;
			}
		}
	}
}