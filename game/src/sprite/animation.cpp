#include <string>
#include "animation.hpp"
#include "../helpers.hpp"

Animation::Animation(std::string name)
	:	reverseonfinish(false),
		currentFrame(0),
		updateTime(0),
		playBackward(false),
		name(name),
		padding(0)
{
}

sf::IntRect Animation::update()
{
	
	//sf::IntRect newRect(currentFrame * width + ((currentFrame + 1) * padding) + startx, starty, (width + currentFrame * width + (currentFrame+1 * padding)), starty + height);
	sf::IntRect newRect = XYWHToLTRB(startx + (currentFrame * width) + (currentFrame * padding), starty, width, height);
	
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
