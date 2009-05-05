#include <SFML/Graphics/Image.hpp>
#include <boost/bind.hpp>

#include "player.hpp"
#include "genericSprite.hpp"
#include "../network/packets.hpp"

#include "../powerup/gun.hpp"

sf::Image Player::Image;

Player::Player(const std::string &name)
	:	 genericSprite(name, "player", Image),
		rolling(false),
		crouching(false),
		running(false),
		idle(false)
{
	spriteType = player;

	
	keyMap[keyLeft]		= false;
	keyMap[keyRight]	= false;
	keyMap[keyDown]		= false;
	keyMap[keyAction]	= false;

	SetX(50);
	changeAnimation("idle");
	setYVelocity(30.0f);
	hasPowerUp = true;
	
	currentPowerup = boost::shared_ptr<genericPowerUp>(new Gun(this));


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
	//rolling = false;
	if (onGround){
		float velocity = (float)(-1*keyMap[keyLeft]+keyMap[keyRight])*30;
		if (velocity != 0){
			if (keyMap[keyDown]){
				rolling = true;
			}else{
				running = true;
			}
			//changeAnimation("run");
			if (velocity < 0){
				flipped = true;
			}else{
				flipped = false;
			}
		}else{
			if (keyMap[keyDown]){
				crouching = true;
			}else{
				if (crouching == true){
					currentAnimation->resume();
					currentAnimation->onFinish.connect(boost::bind(&Player::crouchingFinish, this));
				}
				//crouching = false;
			}
		}
		if ((running + rolling + crouching) > 1){
			throw 0;
		}
		if ((running + rolling + crouching) == 0){
			idle = true;
		}else{
			idle = false;
		}
		if (running && currentAnimation->name != "run"){
			changeAnimation("run");
		}else if (rolling){
			changeAnimation("roll");
		}else if(crouching && currentAnimation->name != "crouch"){
			changeAnimation("crouch");
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