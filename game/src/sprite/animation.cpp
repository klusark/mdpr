#include <string>
#include <iostream>
#include "animation.hpp"
#include "../helpers.hpp"

Animation::Animation(std::string name)
	:	paused(false),
		needsUpdate(false),
		currentFrame(0),
		updateTime(0),
		name(name),
		infoSaved(false),
		needsReset(false)
{
}

Animation::~Animation()
{
}

sf::IntRect Animation::update()
{
	if(!infoSaved){
		OriginalAnimationInfo = AnimationInfo;
		infoSaved = true;
	}
	//sf::IntRect newRect(currentFrame * width + ((currentFrame + 1) * padding) + startx, starty, (width + currentFrame * width + (currentFrame+1 * padding)), starty + height);

	if (!paused){

		updateTime += Clock.GetElapsedTime() * 1000;
		Clock.Reset();

		while(updateTime > AnimationInfo.delay){

			updateTime -= AnimationInfo.delay;
			currentFrame = AnimationInfo.playBackward ? currentFrame -1 : currentFrame + 1;

			if(currentFrame >= AnimationInfo.frames || currentFrame < 0)
			{

				currentFrame = AnimationInfo.playBackward ? AnimationInfo.frames - 1 : 0;
				if (AnimationInfo.pauseOnFinish){
					pause();
					currentFrame = AnimationInfo.playBackward ? 0 : AnimationInfo.frames - 1;
				}
				if (AnimationInfo.reverseOnFinish){
					AnimationInfo.playBackward = true;
				}
				onFinish();
			}
		}
	}else{
		Clock.Reset();
	}
	sf::IntRect newRect = XYWHToLTRB(AnimationInfo.startx + (currentFrame * AnimationInfo.width) + (currentFrame * AnimationInfo.padding), AnimationInfo.starty, AnimationInfo.width, AnimationInfo.height);
	
	return newRect;
	
}

void Animation::resume()
{
	paused = false;
	needsUpdate = true;
}

void Animation::pause()
{
	paused = true;
	needsUpdate = true;
}

void Animation::reset()
{
	AnimationInfo = OriginalAnimationInfo;
	currentFrame = 0;
	Clock.Reset();
	updateTime = 0;
	paused = false;
	needsReset = true;
	needsUpdate = true;
}
