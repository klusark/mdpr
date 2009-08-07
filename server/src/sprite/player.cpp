//#include <boost/bind.hpp>

#include "player.hpp"
#include "genericSprite.hpp"
#include "network/packets.hpp"

#include "powerup/puck.hpp"
#include "helpers.hpp"
#include "animation.hpp"

Player::Player(const std::string &name)
	:	GenericSprite(name, "player"),
		rolling(false),
		crouching(false),
		running(false),
		idle(false),
		jumpingUp(false),
		velocity(0)
{
	spriteType = playerType;

	
	keyMap[keyLeft]		= false;
	keyMap[keyRight]	= false;
	keyMap[keyDown]		= false;
	keyMap[keyUp]		= false;
	keyMap[keyAction]	= false;
	keyMapTwo[keyLeft]	= false;
	keyMapTwo[keyRight]	= false;
	keyMapTwo[keyDown]	= false;
	keyMapTwo[keyUp]	= false;
	keyMapTwo[keyAction]= false;

	changeAnimation("idle");
	setYAccel(50.0f);

	hasPowerUp = true;

	currentPowerup = Poco::SharedPtr<genericPowerUp>(new Puck(this));


}

Player::~Player()
{
}

void Player::update()
{
	if (keyLock){
		wasKeyLocked = true;
		keyMap[keyLeft]		= false;
		keyMap[keyRight]	= false;
		keyMap[keyDown]		= false;
		keyMap[keyUp]		= false;
		keyMap[keyAction]	= false;
	}
	if (!keyLock && wasKeyLocked){
		keyMap[keyLeft]		= keyMapTwo[keyLeft];
		keyMap[keyRight]	= keyMapTwo[keyRight];
		keyMap[keyDown]		= keyMapTwo[keyDown];
		keyMap[keyUp]		= keyMapTwo[keyUp];
		keyMap[keyAction]	= keyMapTwo[keyAction];
	}
	if (currentState == aliveState){
		if ((keyMap[keyAction] == true) && hasPowerUp && (keyMap[keyLeft] + keyMap[keyRight] == 0)){
			currentPowerup->onActionKey();
		}
		running = false;

		if (onGround){
			if (!rolling){
				velocity = (float)(-1 * keyMap[keyLeft] + keyMap[keyRight]) * runSpeed;
			}
			if (jumpingUp){
				jumpingUp = false;
			}
			if (crouching){
				velocity = 0;
			}
			if (velocity != 0){
				if (keyMap[keyDown]){
					rolling = true;
				}else if (rolling){

				}else{
					running = true;
				}

				if (velocity < 0){
					flipped = true;
				}else{
					flipped = false;
				}
			}else if (!rolling){
				if (keyMap[keyDown]){
					crouching = true;
				}else if (crouching){
					currentAnimation->resume();
					//crouchingDown = true;
					//currentAnimation->onFinish = &Player::crouchingFinish;//.connect(boost::bind(&Player::crouchingFinish, this));
					//crouching = false;
				}else if (keyMap[keyUp]){
					jumpingUp = true;
					setYVelocity(-50.0f);
				}
			}
			if ((running + rolling + crouching + jumpingUp) > 1){
				throw 0;
			}
			if ((running + rolling + crouching + jumpingUp) == 0){
				idle = true;
			}else{
				idle = false;
			}
			if (running && currentAnimation->name != "run"){
				changeAnimation("run");
			}else if (rolling && currentAnimation->name != "roll"){
				changeAnimation("roll");
//				currentAnimation->onFinish.connect(boost::bind(&Player::rollingFinish, this));
			}else if(crouching && currentAnimation->name != "crouch"){
				changeAnimation("crouch");
			}else if(jumpingUp && currentAnimation->name != "jumpUp"){
				changeAnimation("jumpUp");
			}else if (idle && currentAnimation->name != "idle"){
				changeAnimation("idle");
			}
			setXVelocity(velocity);
		}
	}
	GenericSprite::update();
}

void Player::crouchingFinish()
{
//	currentAnimation->onFinish.disconnect(boost::bind(&Player::crouchingFinish, this));
	currentAnimation->reset();
	crouching = false;

}

void Player::rollingFinish()
{
	crouching = true;
	rolling = false;
	currentAnimation->reset();
	changeAnimation("crouch");
	currentAnimation->reset();
	currentAnimation->currentFrame = 1;
	currentAnimation->playBackward = true;
	currentAnimation->pause();

}

void Player::onAnimationFinish()
{
	if (rolling == true){
		rollingFinish();
	}
	if (crouching == true && !keyMap[keyDown]){
		crouchingFinish();
	}
}

void Player::death(unsigned short cause)
{
	GenericSprite::death(cause);
	/*if (cause == stringToCRC("gun")){
		currentState = dyingState;
		changeAnimation("dieGun");
		currentAnimation->onFinish.connect(boost::bind(&genericSprite::death, this, cause));
		animationLock = true;
		keyLock = true;
		setXVelocity(0);
	}*/
}
