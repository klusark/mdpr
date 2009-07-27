#ifndef animation_hpp
#define animation_hpp

#include <SFML/System/Clock.hpp>
#include <boost/signal.hpp>

#include <SFML/Graphics/Rect.hpp>

struct AnimationInfoContainer
{
	AnimationInfoContainer()
		:	reverseOnFinish(false),
			pauseOnFinish(false),
			padding(0){}
	int delay, frames, startx, starty, width, height, padding;
	bool pauseOnFinish, reverseOnFinish;
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
	unsigned int CRCName;
	sf::Clock Clock;
	float updateTime;
	unsigned char currentFrame;
	bool paused, needsUpdate, infoSaved, needsReset, playBackward;

	AnimationInfoContainer AnimationInfo;
	AnimationInfoContainer OriginalAnimationInfo;
};

#endif // #ifndef animation_hpp
