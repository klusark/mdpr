#include <SFML/Graphics/Image.hpp>

#include "player.hpp"
#include "genericSprite.hpp"
#include "../network/packets.hpp"

#include "../powerup/gun.hpp"

sf::Image Player::Image;

Player::Player(const std::string &name)
	:	 genericSprite(name, "player", Image),
		rolling(false),
		crouching(false),
		running(false)
{
	spriteType = player;

	
	keyMap[keyLeft]		= false;
	keyMap[keyRight]	= false;
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
				crouching = false;
			}
		}
		if ((running + rolling + crouching) > 1){
			throw 0;
		}
		if (running){
			changeAnimation("run");
		}else if (rolling){
			changeAnimation("roll");
		}else if(crouching){
			changeAnimation("crouch");
		}else{
			changeAnimation("idle");
		}
		setXVelocity(velocity);
	}
#endif
	genericSprite::update();
}
