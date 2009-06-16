#include <boost/bind.hpp>

#include "player.hpp"
#include "genericSprite.hpp"
#include "network/packets.hpp"

#include "../powerup/gun.hpp"

Player::Player(const std::string &name)
	:	 genericSprite(name, "player"),
		rolling(false),
		crouching(false),
		running(false),
		idle(false),
		velocity(0)
{
	spriteType = playerType;

	
	keyMap[keyLeft]		= false;
	keyMap[keyRight]	= false;
	keyMap[keyDown]		= false;
	keyMap[keyUp]		= false;
	keyMap[keyAction]	= false;

	changeAnimation("idle");
	setYVelocity(30.0f);


}

Player::~Player()
{
}

void Player::update()
{
	
	if (keyMap[keyAction] == true && hasPowerUp){
		currentPowerup->onActionKey();
	}
#ifdef SERVER
	running = false;

	if (onGround){
		if (!rolling){
			velocity = (float)(-1*keyMap[keyLeft]+keyMap[keyRight])*30;
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
			//changeAnimation("run");
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
				currentAnimation->onFinish.connect(boost::bind(&Player::crouchingFinish, this));
				//crouching = false;
			}else if (keyMap[keyUp]){
				jumpingUp = true;
			}
		}
		if ((running + rolling + crouching) > 1){
			throw 0;
		}
		if ((running + rolling + crouching ) == 0){
			idle = true;
		}else{
			idle = false;
		}
		if (running && currentAnimation->name != "run"){
			changeAnimation("run");
		}else if (rolling && currentAnimation->name != "roll"){
			changeAnimation("roll");
			currentAnimation->onFinish.connect(boost::bind(&Player::rollingFinish, this));
		}else if(crouching && currentAnimation->name != "crouch"){
			changeAnimation("crouch");
		//}else if(jumpingUp && currentAnimation->name != "jumpingUp"){
		//	changeAnimation("jumpingUp");
		}else if (idle){
			changeAnimation("idle");
		}
		setXVelocity(velocity);
	}
#endif
	genericSprite::update();
}

void Player::crouchingFinish()
{
	currentAnimation->onFinish.disconnect(boost::bind(&Player::crouchingFinish, this));
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

void Player::die()
{
	//changeAnimation
}
