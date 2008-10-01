#include "SDL/SDL.h"
#include <string>
#include <map>
#include "SDL/SDL_image.h"

#include "Player.hpp"
#include "Bubble.hpp"
#include "Effect.hpp"
#include "GameManager.hpp"

/**
 * consturcts the gamemanager
 */
GameManager::GameManager(SDL_Surface *screen, int width, int height, lua_State *luaState) : SpriteManager(screen)
{
	this->height = height;
	this->width = width;
	this->luaState = luaState;
	bActive = false;
	bStartGame = true;
	this->screen = screen;
	loadImages();
	test = 0;
	
}

GameManager::~GameManager()
{

	std::map<std::string, SDL_Surface *>::iterator iter;
    for( iter = images.begin(); iter != images.end(); ++iter ) {
		SDL_FreeSurface(iter->second);

    }
	images.clear();
	delete player1;
	delete player2;
	for (short i = 0; i<3; ++i){
		delete bubbles[i];
	}
}

void GameManager::tick()
{
	if (bStartGame){
		startGame();
		bStartGame = false;
	}
	
	SpriteManager::tick();

	updateLevel();

	drawImageQueue();
	SDL_Flip(screen);
	throttleFPS(60);
}

bool GameManager::isActive()
{
	return bActive;
}

void GameManager::activate()
{
	bActive = true;
}

void GameManager::startGame()
{
	player1 = new Player(this, 1);
	player2 = new Player(this, 2);
	for (short i = 0; i<3; ++i){
		bubbles[i] = new Bubble(this);
	}
	for (short i = 0; i<2; ++i){
		effects[i] = new Effect(this);
	}
	//WeaponManager *weapons = new WeaponManager;
	createLevel();
}

/**
* Calls the functions that create the level
*/
void GameManager::createLevel()
{
	createPlatforms();
	createRopes();
	createMallow();
}

/**
* Creates the platforms
*/
void GameManager::createPlatforms()
{
	short yTemp = 0, xTemp = 0;
	short i, h = 8, w = 14;
	int type = 0,length = 0;
	
	for (i = 0; i <= numPlatforms; ++i){
		if (i == 0){
			//bottom left
			yTemp = 168;
			xTemp = 25;
		}else if (i == 4){
			//bottom right
			xTemp = 233;
		}else if (i == 8){
			//top left
			yTemp = 40;
			xTemp = 49;
		}else if (i == 12){
			//top right
			xTemp = 209;
		}else if (i == 16){
			type = rand() % 2;
			length = 0;
			xTemp = 17;
			yTemp = 72;
		}else if (i == 34){
			type = rand() % 2;
			length = 0;
			xTemp = 17;
			yTemp = 104;
		}else if (i == 52){
			type = rand() % 2;
			length = 0;
			xTemp = 17;
			yTemp = 136;
		}
		if (i < 16){
			platforms[i] = makeRect(h, w, xTemp, yTemp);
			xTemp += 16;
		}else{
			if (length == 0){
				
				if (type == 1){
					type = 0;
				}else{
					type = 1;
				}
				if (type == 1){
					length = rand() % 7 + 1;
				}else{
					length = rand() % 3 + 1;
				}
			}
			if (type == 1){
				--length;
				platforms[i] = makeRect(h, w, xTemp, yTemp);
				xTemp += 16;

			}else{
				--length;
				platforms[i] = makeRect(h, w, 0, 0);
				xTemp += 16;
			}

		}
	}
	
}

/**
* Creates the ropes
*/
void GameManager::createRopes()
{
	ropes[0] = makeRect(152, 1, 80, 16);
	ropes[1] = makeRect(152, 1, 241, 16);
}

/**
* Creates the Marshmallow at the bottom of the screen
*/
void GameManager::createMallow()
{
}

/**
* Updates the ropes, platforms, mallow and emitters
*/
void GameManager::updateLevel()
{
	
	//platform
	for (short i = 0; i < numPlatforms; ++i){
		if (platforms[i].x != 0){
			addToImageQueue(images["platform"], platforms[i], 0);
		}
	}

	//rope
	for (short i = 0; i < numRopes; i++){
		SDL_FillRect(screen, &ropes[i], SDL_MapRGB(screen->format, 144, 96, 0));
	}

	//mallow
	Sint16 x = -test;
	++test;
	if (test >= 64){
		test = 0;
	}

	clearRect(makeRect(16, 320, 0, 184));
	for (; x < width; x+=64)
		addToImageQueue(images["mallow"], makeRect(16, 64, x, 184), 3);
	
}

void GameManager::addToImageQueue(SDL_Surface *image, SDL_Rect rect, short layer)
{
	Queue tempQueue;
	tempQueue.image = image;
	tempQueue.rect = rect;

	imageQueue[layer].push(tempQueue);
}

void GameManager::drawImageQueue()
{
	for (short i = 0; i < 4; ++i){
		while (!imageQueue[i].empty())
		{
			SDL_BlitSurface(imageQueue[i].front().image, 0, screen, &imageQueue[i].front().rect);
			imageQueue[i].pop();
		}
	}
}

void GameManager::clearRect(SDL_Rect rect)
{
	SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));
}

void GameManager::loadImages()
{
	std::string imageList[] = {
		"idle",
		"fall",
		"crouch0",		"crouch1",
		"run0",			"run1",			"run2",			"run3",
		"roll0",		"roll1",		"roll2",		"roll3",
		"climbRope0",	"climbRope1",	"climbRope2",	"climbRope3", 
		"jumpUp0",		"jumpUp1",		"jumpUp2",		"jumpUp3",		"jumpUp4", 
		"jumpForward0",	"jumpForward1",	"jumpForward2",

		"bubblestart0", "bubblestart1", "bubblestart2", 
		"bubble0",		"bubble1",		"bubble2",

		"mallow",

		"platform"
	};
	
	for (short i = 0; i < 32; ++i){
		SDL_RWops *rwop;
		std::string file;
		file += "data/main/";
		file += imageList[i];
		file += ".png";
		rwop = SDL_RWFromFile(file.c_str(), "rb");
		images[imageList[i]] = IMG_LoadPNG_RW(rwop);
		if (!images[imageList[i]])
			printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
		SDL_FreeRW(rwop);
		flippedImages[imageList[i]] = flipImage(images[imageList[i]]);
	}
	
}

SDL_Rect GameManager::makeRect(Uint16 h, Uint16 w, Sint16 x, Sint16 y)
{
	SDL_Rect rect;
	rect.h = h;
	rect.w = w;
	rect.x = x;
	rect.y = y;
	return rect;
}

void GameManager::newEffect(std::string name)
{
	for (short i = 0; i < 2; ++i){
		if (!effects[i]->isInUse()){
			effects[i]->startEffect(name);
			return;
		}
	}
	throw "not enough effects alocated";
}

void GameManager::throttleFPS(short FPS)
{
	Uint32 wait = (Uint32)(1000 / FPS);

	currentTicks = SDL_GetTicks();
	if ((currentTicks - lastTicks) < wait){
		//framerate exceeded limit....so we wait the difference
		SDL_Delay(wait - (currentTicks - lastTicks));
	}
	lastTicks = SDL_GetTicks();

}

Uint32 GameManager::getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	return *(Uint32 *)p;
}

void GameManager::putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = pixel;
}

SDL_Surface *GameManager::flipImage(SDL_Surface *image)
{
	SDL_Surface *flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, image->w, image->h, image->format->BitsPerPixel, image->format->Rmask, image->format->Gmask, image->format->Bmask, image->format->Amask  );
	for( int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx-- )
	{
		for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- )
		{
			putPixel(flipped, rx, y, getPixel(image, x, y));
		}
	}
	return flipped;
}