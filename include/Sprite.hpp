#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SDL/SDL.h"
#include "GameManager.hpp"

class GameManager;

class Sprite
{
	public:
		Sprite(GameManager *);
		virtual ~Sprite();
		void animate();
		virtual void update();
		virtual void animationEnd();
		void move();
		enum collisionTypes
		{
			ground,
			player,
		};
		void setCollisionType(collisionTypes);
		
	protected:
		bool reflip;
		collisionTypes collisionType;

		struct Animation
		{
			///the number of frames in the animation
			short numFrames;
			/// the delay in ms between each frame
			unsigned short delay;
			///an array of all the frames
			char *frames[8];
			/// the current frame
			short currentFrame;

		}*currentAnimation;
		Sprite::Animation *makeAnimaion(short numFrames, Uint16 delay, char *args, ...);
		
		SDL_Rect rect, lastRect;
		SDL_Surface *image;
		Uint32 lastTimeY;
		Uint32 lastTimeX;
		double yMove, xMove, yVelocity, xVelocity;

		/// the layer the sprite should be drawn on
		short layer;

		bool flip;
	private:
		bool moved;

		GameManager *gm;
		Uint32 lastAnimationTime;
};
/*! \class Sprite Sprite.hpp "include/Sprite.hpp"
 *  \brief The Sprite class
 *
 * The Sprite class
 */
#endif
