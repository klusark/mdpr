#ifndef genericSprite_hpp
#define genericSprite_hpp

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Clock.hpp>
#include <map>
#include "../enumerations.hpp"

#include "animation.hpp"

class genericPowerUp;

//! The base sprite class
/*!
All sprites must inherit this class
 Provides movement, animation, and  access to colliiton
*/
class genericSprite : public sf::Sprite
{
public:
	//! The constructor.
	/*!
	Constructs the generic sprite
	\param name Name of the sprite
	\param spriteType Name of the type of sprite. Used for loading the sprites details from a file. 
	\param Image  The static image from the sprite class that inherits this one. 
	*/
	genericSprite(const std::string &name, std::string spriteType, sf::Image &Image);
	//!The deconstructor
	~genericSprite();

	float getXAccel();
	float getYAccel();
	void setXAccel(float xAccel);
	void setYAccel(float yAccel);

	float getXVelocity();
	float getYVelocity();
	void setXVelocity(float xVelocity);
	void setYVelocity(float yVelocity);

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
	virtual void draw(sf::RenderWindow &App);

	//!Changes the current animation of the sprite
	/*!
	\param name name of the sprite that has already been converted into a unsigned int.
	*/
	void changeAnimation(unsigned int name);
	
	//!Changes the current animation of the sprite
	/*!
	\param name in name of the sprite in string form
	*/
	void changeAnimation(std::string name);

	void kill();

	virtual void die();

	//!The name of the sprite
	std::string name;

	//!pointer to the current powerup
	boost::shared_ptr<genericPowerUp> currentPowerup;
	
	//!True if the sprite currently holds a powerup
	bool hasPowerUp,
	
		//!True if the sprite is currently on the groud.
		onGround, 
				
		//!True if the sprite should be server side only.
		nonNetworked, 
		
		//!True if the sprite has its input disabled
		keyLock, 
		
		//!true if the sprite should be locked to it's current animaiton
		animationLock, 
		
		//!ture if the sprite does not have any animation
		noAnimation,
		
		//!true if the sprite is currently flipped.
		flipped;

	//!The name of the last animation. Used to figure out when to send animation change packets.
	std::string lastAnimationName;

	//!The sprite type. Mainly used for collision detection
	spriteTypes spriteType;

	//!Pointer to the current animaiton
	boost::shared_ptr<Animation> currentAnimation;
	
	float lastX, lastY;
	int timesSkiped;
	spriteStates currentState;
protected:
	sf::Image &Image;
	float xAccel,		yAccel;
	float xVelocity,	yVelocity;
	
	sf::Clock Clock;

	typedef std::map<unsigned int, boost::shared_ptr<Animation> > animationContainer;
	animationContainer Animations;
};

#endif // #ifndef genericSprite_hpp
