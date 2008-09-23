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

	SDL_Surface *rollFrames[] = {gm->images["roll0"], gm->images["roll1"], gm->images["roll2"], gm->images["roll3"]};
	rollAnimation = makeAnimaion(4, 100, rollFrames);

	SDL_Surface *crouchFrames[] = {gm->images["crouch0"], gm->images["crouch1"]};
	crouchAnimation = makeAnimaion(2, 100, crouchFrames);

	SDL_Surface *jumpUpFrames[] = {gm->images["jumpup0"], gm->images["jumpup1"], gm->images["jumpup2"], gm->images["jumpup3"], gm->images["jumpup4"]};
	jumpUpAnimation = makeAnimaion(5, 1000, jumpUpFrames);

	SDL_Surface *idleFrames[] = {gm->images["stand"]};
	standAnimation = makeAnimaion(1, 100, idleFrames);

	currentAnimation = standAnimation;

	keyUp = SDLK_w;
	keyDown = SDLK_s;
	keyRight = SDLK_d;
	keyLeft = SDLK_a;

	lastKeystate = SDL_GetKeyState(0);
	isOnGround = false;
	isRunning = false, isRolling = false, isJumpingUp = false, isCrouching = false;
}

/**
 * Deconstrutcs the player
 */
Player::~Player()
{
	delete runAnimation;
	delete standAnimation;
	delete rollAnimation;
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

	isRunning = false, isRolling = false, isCrouching = false, isJumpingUp = false;

	if (isOnGround){
		if (keystate[keyDown]){
			if (keystate[keyRight] || keystate[keyLeft]){
				isRolling = true;
			}else{
				isCrouching = true;
			}
		}else if(keystate[keyUp]){
			if (keystate[keyRight] || keystate[keyLeft]){
				//isRolling = true;
			}else{
				isJumpingUp = true;
			}
		}else{
			if (keystate[keyRight] || keystate[keyLeft]){
				isRunning = true;
			}
		}
	}

	lastKeystate = keystate;
}

void Player::actOnInput()
{
	short test = isRunning + isRolling + isCrouching + isJumpingUp;
	if (test > 1){
		throw "Error more than 1 action set\n";
	}
	if (isRunning){
		currentAnimation = runAnimation;
	}else if (isRolling){
		currentAnimation = rollAnimation;
	}else if (isCrouching){
		currentAnimation = crouchAnimation;
	}else if (isJumpingUp){
		currentAnimation = jumpUpAnimation;
	}else{
		currentAnimation = standAnimation;
	}

	xVelocity = (lastKeystate[keyRight] - lastKeystate[keyLeft]) * walkspeed;
	if (!xVelocity)
		lastTimeX = SDL_GetTicks();
}
