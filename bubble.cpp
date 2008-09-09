#include <SDL.h>
#include "video.hpp"
#include "level.hpp"
#include "game.hpp"
#include "bubble.hpp"

void bubble::update()
{
	SDL_BlitSurface(images[currentFrame], 0, video::screen, &rect);
	if(100 < (SDL_GetTicks() - lastTime) ){
		lastTime = SDL_GetTicks();
		currentFrame++;
		if (currentFrame >= 3)
			currentFrame = 0;
	}
	
	if (game::checkCollision(rect, level::edgeBottom)){
		yMove = -yMove;
	}
	if (game::checkCollision(rect, level::edgeLeft)){
		xMove = -xMove;
	}
	if (game::checkCollision(rect, level::edgeTop)){
		yMove = -yMove;
	}
	if (game::checkCollision(rect, level::edgeRight)){
		xMove = -xMove;
	}
	rect.x += xMove;
	rect.y += yMove;
	
	
	
}

void bubble::init()
{
	
	
	lastTime = SDL_GetTicks();
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
	xMove = rand()%5;
	yMove = rand()%5;
}