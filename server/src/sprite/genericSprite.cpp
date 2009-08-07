#include <Poco/Util/PropertyFileConfiguration.h>
#include <Poco/SharedPtr.h>
#include <Poco/Util/Application.h>

#include <string>
#include <vector>
#include <fstream>
#include <cmath>

#include <SFML/System/Vector2.hpp>
#include "helpers.hpp"

#include "powerup/genericPowerUp.hpp"
#include "genericSprite.hpp"
#include "spriteManager.hpp"
#include "animation.hpp"

GenericSprite::GenericSprite(const std::string &name, std::string spriteType) 
	:	name(name),
		xVelocity(0),
		yVelocity(0),
		xAccel(0),
		yAccel(0),
		lastX(0),
		lastY(0),
		lastFrame(0),
		timesSkiped(0),
		respawnTime(0),
		hasPowerUp(false),
		flipped(false),
		nonNetworked(false),
		animationLock(false),
		keyLock(false),
		noAnimation(false),
		spawnTimerStarted(false),
		currentState(deadState),
		spriteTypeName(spriteType),
		wasKeyLocked(false)
{

	//make the sprite really far away
	SetX((unsigned short)-1);
	SetY((unsigned short)-1);

	loadSprites();
}

GenericSprite::~GenericSprite()
{
}

void GenericSprite::update()
{
	if(currentState == aliveState){
		if(!noAnimation){
			currentAnimation->update();
		}
		float deltaTime = Clock.GetElapsedTime();
		Clock.Reset();

		Move(static_cast<float>(xVelocity*deltaTime+(0.5)*xAccel*pow(deltaTime,2)), static_cast<float>(yVelocity*deltaTime+(0.5)*yAccel*pow(deltaTime,2)));
		xVelocity += xAccel*deltaTime;
		yVelocity += yAccel*deltaTime;

		if (hasPowerUp){
			currentPowerup->update();
		}

	}else if (currentState == deadState){
		if (!spawnTimerStarted){
			spawnTimer.Reset();
			spawnTimerStarted = true;
		}
		if (spawnTimer.GetElapsedTime() >= respawnTime){
			currentState = readyToSpawnState;
			spawnTimerStarted = false;
		}
	}
	//onGround will be set every update by the collition system
	onGround = false;
}

void GenericSprite::changeAnimation(unsigned int name)
{
	if (!animationLock){
		if (Animations.find(name) != Animations.end()){
			currentAnimation = Animations[name];
			currentAnimation->Clock.Reset();
		}else{
			Poco::Util::Application::instance().logger().warning("Error Cannot find Animation: " + name);
			//std::cout << "Error Cannot find Animation: " << name << std::endl;
		}
	}
}
void GenericSprite::onAnimationFinish()
{
}

void GenericSprite::changeAnimation(std::string name)
{
	changeAnimation(stringToCRC(name));
}

void GenericSprite::death(unsigned short cause)
{
	currentState = deadState;
	SetX(unsigned short(-1));
	SetY(unsigned short(-1));
	
}

void GenericSprite::loadSprites()
{
	//load the sprite from a file
	//TODO: add theme support
	std::string file = "data/mdpr/sprites/" + spriteTypeName + "/" + spriteTypeName + ".sprite";
	std::ifstream spriteFileStream(file.c_str());
	if (!spriteFileStream.is_open()){
		//If the file was not found make this sprite not be animated
		noAnimation = true;
		return;
	}

	Poco::Util::PropertyFileConfiguration *propertyFile = new Poco::Util::PropertyFileConfiguration(spriteFileStream);

	std::string str = propertyFile->getString("animation");
	std::string image = propertyFile->getString("image");
	spawnEffect = propertyFile->getString("spawnEffect", "");

	std::vector<std::string> animations = splitString(str, ",");
	{
		std::string fullImageName = "mdpr/sprites/" + spriteTypeName + "/" + image;

		unsigned short spriteID = stringToCRC(spriteTypeName);
		SpriteManager::spriteTypeContainer::iterator iter = sprite.SpriteTypes.find(spriteID);
		if (iter == sprite.SpriteTypes.end()){
			sprite.SpriteTypes[spriteID] = fullImageName;
		}
	}

	
	for (unsigned int i = 0; i < animations.size(); ++i){
		loadSprite(animations[i]);
	}
}

void GenericSprite::loadSprite(std::string name)
{
	Poco::SharedPtr<Animation> newAnimation(new Animation(name, this));
	
	std::string animationFileName = "data/mdpr/sprites/" + spriteTypeName + "/" + name + ".animation";
	Poco::Util::PropertyFileConfiguration *animationPropertyFile = new Poco::Util::PropertyFileConfiguration(animationFileName);
	newAnimation->delay	= animationPropertyFile->getInt("delay");
	newAnimation->frames	= animationPropertyFile->getInt("frames");
	newAnimation->startx	= animationPropertyFile->getInt("startx");
	newAnimation->starty	= animationPropertyFile->getInt("starty");
	newAnimation->width	= animationPropertyFile->getInt("width");
	newAnimation->height	= animationPropertyFile->getInt("height");
	newAnimation->padding	= animationPropertyFile->getInt("padding", 0);
	newAnimation->reverseOnFinish			= animationPropertyFile->getBool("reverseOnFinish", false);
	newAnimation->pauseOnFinish			= animationPropertyFile->getBool("pauseOnFinish", false);
	newAnimation->collisionRect.Top		= animationPropertyFile->getInt("collision.rect.top");
	newAnimation->collisionRect.Bottom	= animationPropertyFile->getInt("collision.rect.bottom");
	newAnimation->collisionRect.Right		= animationPropertyFile->getInt("collision.rect.right");
	newAnimation->collisionRect.Left		= animationPropertyFile->getInt("collision.rect.left");

	unsigned int animationName = stringToCRC(name);
	Animations[animationName] = newAnimation;

	SpriteManager::animationPacketContainer::iterator iter = sprite.Animations.find(animationName);
	if (iter == sprite.Animations.end()){
		animationCreationPacket packet;
		packet.packetID		= animationCreationPacketID;
		packet.animationID	= animationName;
		packet.height		= newAnimation->height;
		packet.width		= newAnimation->width;
		packet.padding		= newAnimation->padding;
		packet.startX		= newAnimation->startx;
		packet.startY		= newAnimation->starty;
		sprite.Animations[packet.animationID] = packet;
	}
}


void GenericSprite::setXAccel(float xAccel)
{
	this->xAccel = xAccel;
}

void GenericSprite::setYAccel(float yAccel)
{
	this->yAccel = yAccel;
}

void GenericSprite::setXVelocity(float xVelocity)
{
	this->xVelocity = xVelocity;
}

void GenericSprite::setYVelocity(float newyVelocity)
{
	yVelocity = newyVelocity;
}

void GenericSprite::SetY(float newY)
{
	y = newY;
}

void GenericSprite::SetX(float newX)
{
	x = newX;
}

Position GenericSprite::GetPosition()
{
	Position pos;
	pos.x = x;
	pos.y = y;
	return pos;
}

void GenericSprite::SetPosition(Position pos)
{
	x = pos.x;
	y = pos.y;
}

void GenericSprite::Move(float xDir, float yDir)
{
	x += xDir;
	y += yDir;
}
