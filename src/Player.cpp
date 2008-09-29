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

	SDL_Surface *crouchDownFrames[] = {gm->images["crouch0"], gm->images["crouch1"]};
	crouchDownAnimation = makeAnimaion(2, 100, crouchDownFrames);
	
	SDL_Surface *crouchUpFrames[] = {gm->images["crouch1"], gm->images["crouch0"]};
	crouchUpAnimation = makeAnimaion(2, 100, crouchUpFrames);

	SDL_Surface *jumpUpFrames[] = {gm->images["jumpUp0"], gm->images["jumpUp1"], gm->images["jumpUp2"], gm->images["jumpUp3"], gm->images["jumpUp4"]};
	jumpUpAnimation = makeAnimaion(5, 100, jumpUpFrames);

	SDL_Surface *crouchedFrames[] = {gm->images["crouch1"]};
	crouchedAnimation = makeAnimaion(1, 100, crouchedFrames);

	SDL_Surface *climbFrames[] = {gm->images["climbRope0"], gm->images["climbRope1"], gm->images["climbRope2"], gm->images["climbRope3"]};
	climbAnimation = makeAnimaion(4, 100, climbFrames);
	
	SDL_Surface *idleFrames[] = {gm->images["idle"]};
	idleAnimation = makeAnimaion(1, 100, idleFrames);

	currentAnimation = idleAnimation;

	keyUp = SDLK_w;
	keyDown = SDLK_s;
	keyRight = SDLK_d;
	keyLeft = SDLK_a;

	lastKeystate = SDL_GetKeyState(0);
	isRunning = false, isRolling = false, isJumpingUp = false, isCrouchingDown = false, isCrouched = false, isCrouchingUp = false, isJumpingForward = false, isJumpingUpStart = false, isClimbingRope = false;
	//layer = 3;
}

/**
 * Deconstrutcs the player
 */
Player::~Player()
{
	delete runAnimation;
	delete idleAnimation;
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

	isRunning = false;
	if (isOnGround){
		if (isCrouchingDown + isCrouched + isRolling + isCrouchingUp + isClimbingRope == 0){
			if (keystate[keyDown]){
				if (keystate[keyRight] || keystate[keyLeft]){
					isRolling = true;
				}else{
					if (isTouchingRope()){
						isClimbingRope = true;
					}else{
						isCrouchingDown = true;
					}
				}
			}else if(keystate[keyUp]){
				if (keystate[keyRight] || keystate[keyLeft]){
					isJumpingForward = true;
				}else{
					if (isTouchingRope()){
						isClimbingRope = true;
					}else{
						isJumpingUp = true;
						isJumpingUpStart = true;
					}
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
	if (isClimbingRope){
		if (keystate[keyRight] || keystate[keyLeft]){
			isClimbingRope = false;
		}
	}

	lastKeystate = keystate;
}

/**
 * acts on all the input for the player
*/
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
	}else if (isClimbingRope){
		currentAnimation = climbAnimation;
	}else{
		currentAnimation = idleAnimation;
	}

	if (isOnGround){
		int xSpeed = walkSpeed * isRunning + rollSpeed * isRolling;
		xVelocity = (lastKeystate[keyRight] - lastKeystate[keyLeft]) * xSpeed;
		if (!xVelocity)
			lastTimeX = SDL_GetTicks();
	}else{
		//lastTimeX = SDL_GetTicks();
	}

	if (isJumpingUpStart){
		yVelocity = jumpUpSpeed;
		isJumpingUpStart = false;
		
	}

	if (isClimbingRope){
		doNotCollideWithPlatform = true;
		if (lastKeystate[keyUp]){
			yVelocity = -ropeSpeed;
		}else if (lastKeystate[keyDown]){
			yVelocity = ropeSpeed;
		}else{
			lastTimeY = SDL_GetTicks();
		}
		collideWithRopeEnds();
	}else{
		doNotCollideWithPlatform = false;
	}
	//It will make more sense later
	//TODO add more factors to the equation

	//if (!yVelocity)
	//	lastTimeY = SDL_GetTicks();
}

/**
 * gets run when an animation ends
 * handles and animation chaning and animation terminating
*/
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
	}else if (isJumpingUp){
		isJumpingUp = false;
	}
}

/**
 * checks if the player is touching the rope
 *
 * @return true if touching false if not touching
*/
bool Player::isTouchingRope()
{
	if (isVerticalOfRect(gm->ropes)){
		return true;
	}
	return false;
}

void Player::collideWithRopeEnds()
{
	move();
	if (yMove > 1 || yMove < -1){
		rect.y -= static_cast<Sint16>(yMove);

		if (!isOverBottomOfRect(gm->ropes) || !isUnderTopOfRect(gm->ropes) && isVerticalOfRect(gm->ropes)){
			rect.y += static_cast<Sint16>(yMove);
			if (isUnderBottomOfRect(gm->ropes)){
				rect.y = gm->ropes.y + gm->ropes.h - rect.h;
				return;
			}else if(isOverTopOfRect(gm->ropes)){
				rect.y = gm->ropes.y;
				return;
			}
			rect.y -= static_cast<Sint16>(yMove);
		}
		rect.y += static_cast<Sint16>(yMove);
	}
}