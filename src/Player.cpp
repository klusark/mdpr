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
	rect = gm->makeRect(24, 24, 50, 0);

	SDL_Surface *runFrames[] = {gm->images["run0"], gm->images["run1"], gm->images["run2"], gm->images["run3"]};
	runAnimation = makeAnimaion(4, 100, runFrames);

	SDL_Surface *rollFrames[] = {gm->images["roll0"], gm->images["roll1"], gm->images["roll2"], gm->images["roll3"]};
	rollAnimation = makeAnimaion(4, 100, rollFrames);

	SDL_Surface *crouchDownFrames[] = {gm->images["crouch0"], gm->images["crouch1"]};
	crouchDownAnimation = makeAnimaion(2, 100, crouchDownFrames);
	
	SDL_Surface *crouchUpFrames[] = {gm->images["crouch1"], gm->images["crouch0"]};
	crouchUpAnimation = makeAnimaion(2, 100, crouchUpFrames);

	SDL_Surface *jumpUpFrames[] = {gm->images["jumpup0"], gm->images["jumpup1"], gm->images["jumpup2"], gm->images["jumpup3"], gm->images["jumpup4"]};
	jumpUpAnimation = makeAnimaion(5, 100, jumpUpFrames);

	SDL_Surface *crouchedFrames[] = {gm->images["crouch1"]};
	crouchedAnimation = makeAnimaion(1, 100, crouchedFrames);


	SDL_Surface *idleFrames[] = {gm->images["stand"]};
	standAnimation = makeAnimaion(1, 100, idleFrames);

	currentAnimation = standAnimation;

	keyUp = SDLK_w;
	keyDown = SDLK_s;
	keyRight = SDLK_d;
	keyLeft = SDLK_a;

	lastKeystate = SDL_GetKeyState(0);
	isRunning = false, isRolling = false, isJumpingUp = false, isCrouchingDown = false, isCrouched = false, isCrouchingUp = false, isJumpingForward = false;;
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

	isRunning = false, isJumpingUp = false;
	if (isOnGround){
		if (isCrouchingDown + isCrouched + isRolling + isCrouchingUp == 0){
			if (keystate[keyDown]){
				if (keystate[keyRight] || keystate[keyLeft]){
					isRolling = true;
				}else{
					isCrouchingDown = true;
				}
			}else if(keystate[keyUp]){
				if (keystate[keyRight] || keystate[keyLeft]){
					isJumpingForward = true;
				}else{
					isJumpingUp = true;
				}
			}else{
				if (keystate[keyRight] || keystate[keyLeft]){
					isRunning = true;
				}
			}
		}else{
			if (!keystate[keyDown]){
				isCrouchingDown = false;
			}
		}
	}

	lastKeystate = keystate;
}

void Player::actOnInput()
{
	//no 2 can be set at the same time
	short test = isRunning + isRolling + isCrouchingDown + isJumpingUp + isCrouched + isCrouchingUp;
	if (test > 1){
		throw "Error more than 1 action set\n";
	}
	if (isRunning){
		currentAnimation = runAnimation;
	}else if (isRolling){
		currentAnimation = rollAnimation;
	}else if (isCrouchingDown){
		currentAnimation = crouchDownAnimation;
	}else if (isJumpingUp){
		currentAnimation = jumpUpAnimation;
	}else if (isCrouched){
		currentAnimation = crouchedAnimation;
	}else if (isCrouchingUp){
		currentAnimation = crouchUpAnimation;
	}else{
		currentAnimation = standAnimation;
	}

	if (isOnGround){
		int xSpeed = walkSpeed * isRunning + rollSpeed * isRolling;
		xVelocity = (lastKeystate[keyRight] - lastKeystate[keyLeft]) * xSpeed;
		if (!xVelocity)
			lastTimeX = SDL_GetTicks();
	}

	//int ySpeed = jumpUpSpeed * isJumpingUp;
	//It will make more sense later
	//TODO add more factors to the equation
	//yVelocity = ySpeed;
	//if (!yVelocity)
	//	lastTimeY = SDL_GetTicks();
}

void Player::animationEnd()
{
	if (isCrouchingDown){
		isCrouchingDown = false;
		isCrouched = true;
	}else if (isCrouched){
		if (!lastKeystate[keyDown]){
			isCrouched = false;
			isCrouchingUp = true;
		}
	}else if (isCrouchingUp) {
		isCrouchingUp = false;
	}else if (isRolling){
		isCrouched = true;
		isRolling = false;
	}
}
