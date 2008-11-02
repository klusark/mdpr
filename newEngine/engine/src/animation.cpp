#include "animation.hpp"
#include "dataTypes.hpp"
#include "graphics.hpp"
#include "engine.hpp"
namespace engine
{
	Animation::Animation()
	{
		lastAnimationTime = SDL_GetTicks();
	}

	Animation::~Animation()
	{
	}

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
				//animationEnd();
			}
		}
		//engine::graphics::drawTexturedQuad(rect, Animations["test"]->frames[0]);
	}

	void Animation::makeAnimation(const char *name, unsigned short numFrames, unsigned short delay, const char *textures, ...)
	{
		animationInfo *animation = new animationInfo;
		animation->delay = delay;
		animation->numFrames = numFrames;
		animation->currentFrame = 0;
		va_list ap;
		int i = 0;

		va_start(ap, textures);
		while (textures != 0 && i < numFrames)
		{
			animation->frames[i] = graphics::textures[textures];
			textures = va_arg(ap, const char *);
			++i;
		}

		va_end(ap);
		Animations[name] = animation;
	}

	void Animation::changeAnimation(const char *name)
	{
		currentAnimation = Animations[name];
		currentAnimation->currentFrame = 0;

	}
}
