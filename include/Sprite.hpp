#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SDL.h"

class GameManager;
struct SDL_Rect;

class Sprite
{
	public:
		Sprite(GameManager *);
		~Sprite();
		void animate();
		void update();
		void move(short, short);
		enum collisionTypes
		{
			ground,
			player,
		};
		void setCollisionType(collisionTypes);
	protected:
		collisionTypes collisionType;

		struct animation
		{
			///the number of frames in the animation
			short numFrames;
			/// the delay in ms between each frame
			short delay;
			///an array of all the frames
			int frames[8];

		};
		SDL_Rect rect;
		SDL_Surface *image;
	private:
		GameManager *gm;
};
/*! \class Sprite Sprite.hpp "include/Sprite.hpp"
 *  \brief The Sprite class
 *
 * The Sprite class
 */
#endif
