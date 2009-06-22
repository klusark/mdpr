#ifndef clientSprite_hpp
#define clientSprite_hpp

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

//! The base sprite class
/*!
All sprites must inherit this class
 Provides movement, animation, and  access to colliiton
*/
class ClientSprite : public sf::Sprite
{
public:
	//! The constructor.
	/*!
	Constructs the generic sprite
	\param name Name of the sprite
	\param spriteType Name of the type of sprite. Used for loading the sprites details from a file. 
	\param Image  The static image from the sprite class that inherits this one. 
	*/
	ClientSprite(const std::string &name);

	//!The deconstructor
	~ClientSprite();


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

	//!The name of the sprite
	std::string name;

	unsigned short currentAnimationID, currentFrame;

	//!true if the sprite is currently flipped.
	bool flipped;
};

#endif // #ifndef clientSprite_hpp
