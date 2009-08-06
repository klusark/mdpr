#include <string>
#include "animation.hpp"
#include "helpers.hpp"

Animation::Animation(std::string name)
	:	paused(false),
		currentFrame(0),
		updateTime(0),
		name(name),
		playBackward(false),
		reverseOnFinish(false),
		pauseOnFinish(false),
		padding(0)
{
	CRCName = stringToCRC(name);
}

Animation::~Animation()
{
}

sf::IntRect Animation::update()
{
	
	if (!paused){

		updateTime += Clock.GetElapsedTime() * 1000;
		Clock.Reset();

		while(updateTime > delay){

			updateTime -= delay;
			currentFrame = playBackward ? currentFrame -1 : currentFrame + 1;

			if(currentFrame >= frames || currentFrame < 0)
			{

				currentFrame = playBackward ? frames - 1 : 0;
				if (pauseOnFinish){
					pause();
					currentFrame = playBackward ? 0 : frames - 1;
				}
				if (reverseOnFinish){
					playBackward = true;
				}
				onFinish();
			}
		}
	}else{
		Clock.Reset();
	}
	sf::IntRect newRect = XYWHToLTRB(startx + (currentFrame * width) + (currentFrame * padding), starty, width, height);
	
	return newRect;
	
}

void Animation::resume()
{
	paused = false;
}

void Animation::pause()
{
	paused = true;
}

void Animation::reset()
{
	currentFrame = 0;
	Clock.Reset();
	updateTime = 0;
	paused = false;
	playBackward = false;
}
