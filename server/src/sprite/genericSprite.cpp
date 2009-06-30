#include <boost/program_options.hpp>
#include <Poco/SharedPtr.h>
#include <boost/thread.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

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

	std::string file;

	file = "data/mdpr/sprites/";
	file += spriteType;
	file += "/";
	file += spriteType;
	file += ".sprite";

	std::ifstream spriteFileStream(file.c_str());
	if (!spriteFileStream.is_open()){
		noAnimation = true;
		return;
	}

	std::vector<std::string> animations;
	std::string image;
	boost::program_options::options_description spriteConfig("Configuration");
	spriteConfig.add_options()
		("animation",	boost::program_options::value<std::vector<std::string> >(&animations),	"")
		("image",		boost::program_options::value<std::string>(&image),						"")
		("spawnEffect",	boost::program_options::value<std::string>(&spawnEffect),				"");

	boost::program_options::variables_map spriteVariableMap;

	boost::program_options::options_description spriteConfigFileOptions;
	spriteConfigFileOptions.add(spriteConfig);

	boost::program_options::store(parse_config_file(spriteFileStream, spriteConfigFileOptions), spriteVariableMap);
	notify(spriteVariableMap);

	{
		std::string fullImageName;
		fullImageName = "mdpr/sprites/";
		fullImageName += spriteType;
		fullImageName += "/";
		fullImageName += image;

		unsigned short spriteID = stringToCRC(spriteType);
		spriteManager::spriteTypeContainer::iterator iter = sprite.SpriteTypes.find(spriteID);
		if (iter == sprite.SpriteTypes.end()){
			sprite.SpriteTypes[spriteID] = fullImageName;
		}
	}

	std::vector<std::string>::iterator iter;
	for (iter = animations.begin(); iter < animations.end(); ++iter){

		boost::program_options::options_description animationConfig("Configuration");
		Poco::SharedPtr<Animation> newAnimation(new Animation(*iter));
		
		animationConfig.add_options()
			("delay",	boost::program_options::value<int>(&newAnimation->AnimationInfo.delay),		"")
			("frames",	boost::program_options::value<int>(&newAnimation->AnimationInfo.frames),	"")
			("startx",	boost::program_options::value<int>(&newAnimation->AnimationInfo.startx),	"")
			("starty",	boost::program_options::value<int>(&newAnimation->AnimationInfo.starty),	"")
			("width",	boost::program_options::value<int>(&newAnimation->AnimationInfo.width),		"")
			("height",	boost::program_options::value<int>(&newAnimation->AnimationInfo.height),	"")
			("padding",	boost::program_options::value<int>(&newAnimation->AnimationInfo.padding),	"")
			("reverseOnFinish",			boost::program_options::value<bool>(&newAnimation->AnimationInfo.reverseOnFinish),		"")
			("pauseOnFinish",			boost::program_options::value<bool>(&newAnimation->AnimationInfo.pauseOnFinish),		"")

			("collision.rect.top",		boost::program_options::value<int>(&newAnimation->AnimationInfo.collisionRect.Top),	"")
			("collision.rect.bottom",	boost::program_options::value<int>(&newAnimation->AnimationInfo.collisionRect.Bottom),	"")
			("collision.rect.right",	boost::program_options::value<int>(&newAnimation->AnimationInfo.collisionRect.Right),	"")
			("collision.rect.left",		boost::program_options::value<int>(&newAnimation->AnimationInfo.collisionRect.Left),	"");

		boost::program_options::variables_map animationVariableMap;

		boost::program_options::options_description animationConfigFileOptions;
		animationConfigFileOptions.add(animationConfig);
		
		std::string animationFileName;
		animationFileName = "data/mdpr/sprites/";
		animationFileName += spriteType;
		animationFileName += "/";
		animationFileName += *iter;
		animationFileName += ".animation";

		std::ifstream animationFileStream(animationFileName.c_str());

		boost::program_options::store(parse_config_file(animationFileStream, animationConfigFileOptions), animationVariableMap);
		notify(animationVariableMap);
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
			std::cout << "Error Cannot find Animation: " << name << std::endl;
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
