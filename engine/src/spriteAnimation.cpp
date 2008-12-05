#include "engineLib.hpp"
#include "spriteAnimation.hpp"
#include "dataTypes.hpp"
#include "graphics.hpp"
#include "engine.hpp"
#include <map>
#include <string>

namespace engine
{

	/**
	 * Initialize The Animation System for the sprite
	 */
	Animation::Animation()
	{
		
		lastAnimationTime = SDL_GetTicks();
	}

	/**
	 * Destroys The Animation System for the sprite
	 */
	Animation::~Animation()
	{
	}

	/**
	 * Updates The Animation System for the sprite
	 * Takes care of chaning the current image
	 */
	void Animation::update()
	{
		Rect rect = engine::makeRect(55, 22, 24, 24);
		//animationInfo *currentAnimation = Animations["test"];
		if(currentAnimation->delay < (SDL_GetTicks() - lastAnimationTime)){
			engine::graphics::drawTexturedQuad(rect, currentAnimation->frames[currentAnimation->currentFrame]);
			lastAnimationTime = SDL_GetTicks();
			++currentAnimation->currentFrame;
			if (currentAnimation->currentFrame >= currentAnimation->numFrames){
				currentAnimation->currentFrame = 0;
			}
		}
		//engine::graphics::drawTexturedQuad(rect, Animations["test"]->frames[0]);
	}

	/**
	 * Makes a animation and stores it in the Animations map
	 * @param name the name of the animation
	 * @param numFrames The number of frames in the animation
	 * @param delay The delay in miliseconds between frames
	 * @param frames The names of the freams
	 */
	void Animation::makeAnimation(std::string name, unsigned short numFrames, unsigned short delay, std::string frames)
	{
		animationInfo *animation = new animationInfo;
		animation->name = name;
		animation->delay = delay;
		animation->numFrames = numFrames;
		animation->currentFrame = 0;
		//animation->frameNames = new std::string[numFrames];
		char *str = const_cast<char *>(frames.c_str());
		char *tmp;
		int i = 0;
		tmp = strtok(str, ",");
		while(i<numFrames){
			animation->frames[i] = graphics::textures[tmp];
			//animation->frameNames[i] = tmp;

			tmp = strtok(str, ",");
			++i;
		}
		/*va_list ap;
		int i = 0;

		va_start(ap, textures);
		while (textures != 0 && i < numFrames)
		{
			animation->frames[i] = graphics::textures[textures];
			textures = va_arg(ap, const char *);
			++i;
		}

		va_end(ap);*/
		Animations[name] = animation;
	}

	/**
	 * Changes the animation to the given animation name
	 * @param name The name of the animation to change to
	 */
	void Animation::changeAnimation(const char *name)
	{
		currentAnimation = Animations[name];
		currentAnimation->currentFrame = 0;

	}

	std::string Animation::getName()
	{
		return "animation";
	}
}
