#include "GameManager.hpp"

bool running = true;

/**
 * Main function for the game
 */
int main()
{
	GameManager *gm = new GameManager;
	//main loop
	gm->activate();
	while (running)
	{
		if (gm->isActive())
			gm->tick();
	}
	return 0;
}
/*! \mainpage Marshmallow Duel: Percy's Return
*/
