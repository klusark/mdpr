#include "GameManager.hpp"
#include "Player.hpp"

/**
 * Constructs the player
 */
Player::Player(GameManager *gm, short playerNum) : Mass(gm)
{
	this->gm = gm;
	this->playerNum = playerNum;
	setCollisionType(player);
	rect = gm->makeRect(24, 24, 50, 50);

	SDL_Surface *runFrames[] = {gm->images["run0"], gm->images["run1"], gm->images["run2"], gm->images["run3"]};
	runAnimation = makeAnimaion(4, 100, runFrames);

	SDL_Surface *idleFrames[] = {gm->images["stand"]};
	standAnimation = makeAnimaion(1, 100, idleFrames);

	currentAnimation = standAnimation;

	keyUp = SDLK_w;
	keyDown = SDLK_s;
	keyRight = SDLK_d;
	keyLeft = SDLK_a;

	lastKeystate = SDL_GetKeyState(0);
	isRunning = false, isRolling = false, isOnGround = false;
}

/**
 * Deconstrutcs the player
 */
Player::~Player()
{
	delete runAnimation;
	delete standAnimation;
}

/**
 * Update the player
 */
void Player::update()
{
	//get the input
	input();
	actOnInput();
	Mass::update();
	
}

/**
 * Gets all the input for the player 
 */
void Player::input()
{
	Uint8 *keystate = SDL_GetKeyState(0);
	isRunning = false;
	if (isOnGround){
		if (keystate[keyRight] || keystate[keyLeft]){
			isRunning = true;
		}
	}

	lastKeystate = keystate;
}

void Player::actOnInput()
{
	if (isRunning){
		currentAnimation = runAnimation;
	}else{
		lastTimeX = SDL_GetTicks();
		currentAnimation = standAnimation;
	}

	xVelocity = (lastKeystate[keyRight] - lastKeystate[keyLeft]) * walkspeed;
}
