#ifndef animaiton_hpp
#define animation_hpp
#include "sprite.hpp"
#include "spriteInterface.hpp"
#include <map>
#include <string>
namespace engine
{
	class  Animation : public spriteInterface
	{
	private:
		struct animationInfo
		{
			///the number of frames in the animation
			unsigned short numFrames;
			/// the delay in ms between each frame
			unsigned short delay;
			///an array of all the frames
			unsigned int frames[8];
			/// the current frame
			unsigned short currentFrame;
		} *currentAnimation;
		unsigned int lastAnimationTime;
		std::map<std::string, animationInfo *> Animations;
	public:
		EngineLib Animation();
		virtual EngineLib ~Animation();
		virtual EngineLib void update();
		void EngineLib makeAnimation(const char *name, unsigned short numFrames, unsigned short delay, const char *textures, ...);
		void EngineLib changeAnimation(const char *name);
	};
}
#endif
