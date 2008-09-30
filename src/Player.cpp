#include "Player.hpp"

/**
 * Constructs the player
 */
Player::Player(GameManager *gm, short playerNum) : Mass(gm)
{
	this->gm = gm;
	this->playerNum = playerNum;
	setCollisionType(player);
	rect = gm->makeRect(24, 24, 28, 144);


	runAnimation = makeAnimaion(4, 100, "run0", "run1", "run2", "run3");


	rollAnimation = makeAnimaion(4, 100, "roll0", "roll1", "roll2", "roll3");


	crouchDownAnimation = makeAnimaion(2, 100, "crouch0", "crouch1");
	

	crouchUpAnimation = makeAnimaion(2, 100, "crouch1", "crouch0");


	jumpUpAnimation = makeAnimaion(5, 100, "jumpUp0", "jumpUp1", "jumpUp2", "jumpUp3", "jumpUp4");


	crouchedAnimation = makeAnimaion(1, 100, "crouch1");


	climbAnimation = makeAnimaion(4, 100, "climbRope0", "climbRope1", "climbRope2", "climbRope3");
	

	idleAnimation = makeAnimaion(1, 100, "idle");

	currentAnimation = idleAnimation;
	
	if (playerNum == 1){
		keyUp = SDLK_w;
		keyDown = SDLK_s;
		keyRight = SDLK_d;
		keyLeft = SDLK_a;
	}else{
		flip = true;
		keyUp = SDLK_UP;
		keyDown = SDLK_DOWN;
		keyRight = SDLK_RIGHT;
		keyLeft = SDLK_LEFT;
		rect.x = 270;
	}

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
	short test = isRunning + isRolling + isCrouchingDown + isJumpingUp + isCrouched + isCrouchingUp + isClimbingRope;
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