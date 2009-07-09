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

	SetX((unsigned short)-1);
	SetY((unsigned short)-1);

	std::string file = "data/mdpr/sprites/" + spriteType + "/" + spriteType + ".sprite";
	std::ifstream spriteFileStream(file.c_str());
	if (!spriteFileStream.is_open()){
		noAnimation = true;
		return;
	}

	Poco::Util::PropertyFileConfiguration *propertyFile = new Poco::Util::PropertyFileConfiguration(spriteFileStream);

	std::string str = propertyFile->getString("animation");
	std::string image = propertyFile->getString("image");
	spawnEffect = propertyFile->getString("spawnEffect", "");

	std::vector<std::string> animations;
	int cutAt;
	while((cutAt = str.find_first_of(",")) != str.npos ){
		if(cutAt > 0){
			animations.push_back(str.substr(0, cutAt));
		}
		str = str.substr(cutAt+1);
	}
	if(str.length() > 0){
		animations.push_back(str);
	}
	
	/*std::ifstream spriteFileStream(file.c_str());
	if (!spriteFileStream.is_open()){
		noAnimation = true;
		return;
	}*/

	/*
	spriteConfig.add_options()
		("animation",	boost::program_options::value<std::vector<std::string> >(&animations),	"")
		("image",		boost::program_options::value<std::string>(&image),						"")
		("spawnEffect",	boost::program_options::value<std::string>(&spawnEffect),				"");


*/
	{
		
		std::string fullImageName = "mdpr/sprites/" + spriteType + "/" + image;

		unsigned short spriteID = stringToCRC(spriteType);
		spriteManager::spriteTypeContainer::iterator iter = sprite.SpriteTypes.find(spriteID);
		if (iter == sprite.SpriteTypes.end()){
			sprite.SpriteTypes[spriteID] = fullImageName;
		}
	}

	std::vector<std::string>::iterator iter;
	for (iter = animations.begin(); iter < animations.end(); ++iter){

		
		Poco::SharedPtr<Animation> newAnimation(new Animation(*iter));
		
		std::string animationFileName = "data/mdpr/sprites/" + spriteType + "/" + *iter + ".animation";
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

		unsigned int animationName = stringToCRC(*iter);
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
