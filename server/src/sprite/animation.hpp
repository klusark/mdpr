#ifndef animation_hpp
#define animation_hpp

#include <SFML/System/Clock.hpp>
//#include <boost/signal.hpp>

#include <SFML/Graphics/Rect.hpp>

class GenericSprite;

//!handles animations
class Animation
{
public:
	//!Constructor
	/*!
	@param name the name of the animation
	*/
	Animation(std::string name, GenericSprite *owner);
	~Animation();

	//!update the animation
	/*!
	@return the sub rect of the current frame
	*/
	sf::IntRect update();

	//!Pauses the animation
	void pause();

	//!resumes the animaiton
	void resume();

	//!resets the animation to the initial satate
	void reset();

	//!Signal that gets run when the animation ends
	//boost::signal<void ()> onFinish;

	//void (*onFinish)();

	//!Name of the animation
	std::string name;

	//!the name of the animation precrcd
	unsigned int CRCName;

	//!clock for timing the framges
	sf::Clock Clock;

	//!the time since the last frame change
	float updateTime;

	//!the current frame
	unsigned char currentFrame;

	//!ture if currently paused
	bool paused, 
		//!ture and the animation will play backwards
		playBackward, 
		//!true and the animation will pause when it finishes
		pauseOnFinish, 
		//!true and the animation will reverse after it finishes
		reverseOnFinish;
	
	//!The delay between frames
	int delay, 
		//!The number of frames
		frames, 
		//!the x position in the image where this animaiton starts
		startx, 
		//!the y position in the image where this animaiton starts
		starty, 
		//!the width of the frames
		width, 
		//!the height of the frames
		height, 
		//!the padding between the frames
		padding;

	//!the rect for checking collisions
	sf::IntRect collisionRect;

	GenericSprite *owner;
};

#endif // #ifndef animation_hpp
