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

genericSprite::genericSprite(const std::string &name, std::string spriteType) 
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

genericSprite::~genericSprite()
{
}

void genericSprite::update()
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

void genericSprite::changeAnimation(unsigned int name)
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

void genericSprite::changeAnimation(std::string name)
{
	changeAnimation(stringToCRC(name));
}

void genericSprite::death(unsigned short cause)
{
	currentState = deadState;
	SetX(unsigned short(-1));
	SetY(unsigned short(-1));
	
}

void genericSprite::loadSprites()
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
		spriteManager::spriteTypeContainer::iterator iter = sprite.SpriteTypes.find(spriteID);
		if (iter == sprite.SpriteTypes.end()){
			sprite.SpriteTypes[spriteID] = fullImageName;
		}
	}

	
	for (unsigned int i = 0; i < animations.size(); ++i){
		loadSprite(animations[i]);
	}
}

void genericSprite::loadSprite(std::string name)
{
	Poco::SharedPtr<Animation> newAnimation(new Animation(name));
	
	std::string animationFileName = "data/mdpr/sprites/" + spriteTypeName + "/" + name + ".animation";
	Poco::Util::PropertyFileConfiguration *animationPropertyFile = new Poco::Util::PropertyFileConfiguration(animationFileName);
	newAnimation->AnimationInfo.delay	= animationPropertyFile->getInt("delay");
	newAnimation->AnimationInfo.frames	= animationPropertyFile->getInt("frames");
	newAnimation->AnimationInfo.startx	= animationPropertyFile->getInt("startx");
	newAnimation->AnimationInfo.starty	= animationPropertyFile->getInt("starty");
	newAnimation->AnimationInfo.width	= animationPropertyFile->getInt("width");
	newAnimation->AnimationInfo.height	= animationPropertyFile->getInt("height");
	newAnimation->AnimationInfo.padding	= animationPropertyFile->getInt("padding", 0);
	newAnimation->AnimationInfo.reverseOnFinish			= animationPropertyFile->getBool("reverseOnFinish", false);
	newAnimation->AnimationInfo.pauseOnFinish			= animationPropertyFile->getBool("pauseOnFinish", false);
	newAnimation->AnimationInfo.collisionRect.Top		= animationPropertyFile->getInt("collision.rect.top");
	newAnimation->AnimationInfo.collisionRect.Bottom	= animationPropertyFile->getInt("collision.rect.bottom");
	newAnimation->AnimationInfo.collisionRect.Right		= animationPropertyFile->getInt("collision.rect.right");
	newAnimation->AnimationInfo.collisionRect.Left		= animationPropertyFile->getInt("collision.rect.left");

	unsigned int animationName = stringToCRC(name);
	Animations[animationName] = newAnimation;

	spriteManager::animationPacketContainer::iterator iter = sprite.Animations.find(animationName);
	if (iter == sprite.Animations.end()){
		animationCreationPacket packet;
		packet.packetID		= animationCreationPacketID;
		packet.animationID	= animationName;
		packet.height		= newAnimation->AnimationInfo.height;
		packet.width		= newAnimation->AnimationInfo.width;
		packet.padding		= newAnimation->AnimationInfo.padding;
		packet.startX		= newAnimation->AnimationInfo.startx;
		packet.startY		= newAnimation->AnimationInfo.starty;
		sprite.Animations[packet.animationID] = packet;
	}
}

float genericSprite::getXAccel()
{
	return xAccel;
}

float genericSprite::getYAccel()
{
	return yAccel;
}

void genericSprite::setXAccel(float xAccel)
{
	this->xAccel = xAccel;
}

void genericSprite::setYAccel(float yAccel)
{
	this->yAccel = yAccel;
}

float genericSprite::getXVelocity()
{
	return xVelocity;
}

float genericSprite::getYVelocity()
{
	return yVelocity;
}

void genericSprite::setXVelocity(float xVelocity)
{
	this->xVelocity = xVelocity;
}

void genericSprite::setYVelocity(float newyVelocity)
{
	yVelocity = newyVelocity;
}

void genericSprite::SetY(float newY)
{
	y = newY;
}

void genericSprite::SetX(float newX)
{
	x = newX;
}

float genericSprite::GetX()
{
	return x;
}

float genericSprite::GetY()
{
	return y;
}

Position genericSprite::GetPosition()
{
	Position pos;
	pos.x = x;
	pos.y = y;
	return pos;
}

void genericSprite::SetPosition(Position pos)
{
	x = pos.x;
	y = pos.y;
}

void genericSprite::Move(float xDir, float yDir)
{
	x += xDir;
	y += yDir;
}
