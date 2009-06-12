#include <string>
#include <iostream>
#include "animation.hpp"
#include "helpers.hpp"

Animation::Animation(std::string name)
	:	paused(false),
		needsUpdate(false),
		currentFrame(0),
		updateTime(0),
		name(name),
		infoSaved(false),
		needsReset(false),
		playBackward(false)
{
	CRCName = stringToCRC(name);
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
#if SERVER
	if (!paused){

		updateTime += Clock.GetElapsedTime() * 1000;
		Clock.Reset();

		while(updateTime > AnimationInfo.delay){

			updateTime -= AnimationInfo.delay;
			currentFrame = playBackward ? currentFrame -1 : currentFrame + 1;

			if(currentFrame >= AnimationInfo.frames || currentFrame < 0)
			{

				currentFrame = playBackward ? AnimationInfo.frames - 1 : 0;
				if (AnimationInfo.pauseOnFinish){
					pause();
					currentFrame = playBackward ? 0 : AnimationInfo.frames - 1;
				}
				if (AnimationInfo.reverseOnFinish){
					playBackward = true;
				}
				onFinish();
			}
		}
	}else{
		Clock.Reset();
	}
#endif
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
	//AnimationInfo = OriginalAnimationInfo;
	currentFrame = 0;
	Clock.Reset();
	updateTime = 0;
	paused = false;
	playBackward = false;
	//needsReset = true;
	//needsUpdate = true;
}
