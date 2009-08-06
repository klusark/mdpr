#ifndef genericSprite_hpp
#define genericSprite_hpp

#include <Poco/SharedPtr.h>
#include <SFML/System/Clock.hpp>
#include <map>
#include "enumerations.hpp"

#include "animation.hpp"

class genericPowerUp;

struct Position
{
	float x,y;
};

//! The base sprite class
/*!
All sprites must inherit this class
Provides movement, animation, and  access to colliiton
*/
class GenericSprite
{
public:
	//! The constructor.
	/*!
	Constructs the generic sprite
	\param name Name of the sprite
	\param spriteType Name of the type of sprite. Used for loading the sprites details from a file. 
	\param Image  The static image from the sprite class that inherits this one. 
	*/
	GenericSprite(const std::string &name, std::string spriteType);

	//!The deconstructor
	~GenericSprite();

	//!Updates the sprite
	/*!
	Can be reimplemented in an inheritor for more updating control
	*/
	virtual void update();
	
	//!Draws the sprite to the screen
	/*!
	Can be reimplemented in an inheritor for more drawing control
	\param App The render window to draw the sprite onto. 
	*/
	//virtual void draw(sf::RenderWindow &App);

	//!Changes the current animation of the sprite
	/*!
	@param name name of the sprite that has already been converted into a unsigned int.
	*/
	void changeAnimation(unsigned int name);
	
	//!Changes the current animation of the sprite
	/*!
	@param name in name of the sprite in string form
	*/
	void changeAnimation(std::string name);

	//!Loads all the sprites
	void loadSprites();

	//!Loads a sprite from file
	/*!
	@param name the name of the sprite to load
	*/
	void loadSprite(std::string name);

	//!Kills the sprite
	/*!
	\param cause the crc of the name of the cause
	*/
	virtual void death(unsigned short cause);

	//!The name of the sprite
	std::string name;

	//!pointer to the current powerup
	Poco::SharedPtr<genericPowerUp> currentPowerup;
	
	//!True if the sprite currently holds a powerup
	bool hasPowerUp,
	
		//!True if the sprite is currently on the groud.
		onGround, 
				
		//!True if the sprite should be server side only.
		nonNetworked, 
		
		//!True if the sprite has its input disabled
		keyLock,

		//!true if the keys were locked
		wasKeyLocked,
		
		//!true if the sprite should be locked to it's current animaiton
		animationLock, 
		
		//!ture if the sprite does not have any animation
		noAnimation,
		
		//!true if the sprite is currently flipped.
		flipped,

		//!true of the spawn timer has been started
		spawnTimerStarted;

	//!The name of the last animation. Used to figure out when to send animation change packets.
	std::string lastAnimationName;

	//!The last frame sent to the clients
	unsigned short lastFrame;

	//!The sprite type. Mainly used for collision detection
	spriteTypes spriteType;

	std::string spriteTypeName;

	//!Pointer to the current animaiton
	Poco::SharedPtr<Animation> currentAnimation;

	//!The effect to show when this sprite spawns
	std::string spawnEffect;

	//!The timer used for timing respawn.
	sf::Clock spawnTimer;

	//!The amount of time it takes for this sprite to respawn.
	unsigned short respawnTime; 
	
	float lastX, lastY;
	int timesSkiped;
	spriteStates currentState;

	
	float getXAccel() const {return xAccel;};
	float getYAccel() const {return yAccel;};
	void setXAccel(float xAccel);
	void setYAccel(float yAccel);

	float getXVelocity() const {return xVelocity;};
	float getYVelocity() const {return yVelocity;};
	void setXVelocity(float xVelocity);
	void setYVelocity(float yVelocity);

	void SetY(float);
	void SetX(float);
	float GetX() const {return x;};
	float GetY() const {return y;};
	Position GetPosition();
	void SetPosition(Position);
	void Move(float,float);
protected:
	float xAccel,		yAccel;
	float xVelocity,	yVelocity;
	float x,			y;
	
	sf::Clock Clock;

	typedef std::map<unsigned int, Poco::SharedPtr<Animation> > animationContainer;
	animationContainer Animations;
};

#endif // #ifndef genericSprite_hpp
