#include "animation.hpp"
#include "dataTypes.hpp"
#include "graphics.hpp"
#include "engine.hpp"
namespace engine
{
	Animation::Animation()
	{

	}

	Animation::~Animation()
	{
	}

	void Animation::update()
	{
		Rect rect = engine::makeRect(55, 22, 24, 24);

		engine::graphics::drawTexturedQuad(rect, Animations["test"]->frames[0]);
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
}
