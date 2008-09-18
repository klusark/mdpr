#ifndef BUBBLE_HPP
#define BUBBLE_HPP

#include "Sprite.hpp"

class GameManager;

class Bubble : public Sprite
{
	public:
		Bubble(GameManager *);
		~Bubble();
		void update();
	private:
		GameManager *gm;
};

/*! \class Bubble Bubble.hpp "include/Bubble.hpp"
 *  \brief The Bubble class
 *
 * The Bubble class
 */

#endif
