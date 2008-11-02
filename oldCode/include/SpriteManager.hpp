#ifndef SPRITEANAGER_HPP
#define SPRITEANAGER_HPP



class Player;
class Bubble;
class Effect;
struct SDL_Surface;

class SpriteManager
{
	public:
		SpriteManager(SDL_Surface *);
		~SpriteManager();
		void tick();
		void checkCollions();

	protected:
		Player *player1;
		Player *player2;
		Bubble *bubbles[3];
		Effect *effects[2];

	private:
		SDL_Surface *screen;
};
/*! \class SpriteManager SpriteManager.hpp "include/SpriteManager.hpp"
 *  \brief The SpriteManager class
 *
 * The SpriteManager class
 */
#endif
