#ifndef animation_hpp
#define animation_hpp

#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <boost\signal.hpp>

struct AnimationInfoContainer
{
	AnimationInfoContainer():reverseOnFinish(false),
		pauseOnFinish(false),playBackward(false),padding(0){}
	int delay, frames, startx, starty, width, height, padding;
	bool playBackward, pauseOnFinish, reverseOnFinish;
	sf::IntRect collisionRect;

};

class Animation
{
public:
	Animation(std::string name);
	~Animation();
	sf::IntRect update();
	void pause();
	void resume();
	void reset();
	boost::signal<void ()> onFinish;
	std::string name;
	sf::Clock Clock;
	float updateTime;
	int currentFrame;
	bool paused, needsUpdate, infoSaved, needsReset;

	AnimationInfoContainer AnimationInfo;
	AnimationInfoContainer OriginalAnimationInfo;
};



#endif // ifndef animation_hpp
