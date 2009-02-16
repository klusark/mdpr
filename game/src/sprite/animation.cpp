#include <string>
#include "animation.hpp"

Animation::Animation(std::string name)
	:	reverseonfinish(false),
		currentFrame(0),
		updateTime(0),
		playBackward(false),
		name(name)
{
}

sf::IntRect Animation::update()
{
	
	sf::IntRect newRect(currentFrame * width + startx, starty, (width + currentFrame * width) -1, starty + height);

	updateTime += Clock.GetElapsedTime() * 1000;
	Clock.Reset();
	while(updateTime > delay){
		updateTime -= delay;
		currentFrame = playBackward ? currentFrame -1 : currentFrame + 1;
		
		if(currentFrame >= frames || currentFrame < 0)
		{
			currentFrame = playBackward ? frames - 1 : 0;
		}
	}

	return newRect;
	
}
