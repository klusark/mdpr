#include "GameManager.hpp"

/**
 * Main function for the game
 */
int main()
{
	GameManager *gm = new GameManager;
	//main loop
	gm->activate();
	try
	{
		//go untill an exception is raised
		while (1)
		{
			if (gm->isActive())
				gm->tick();
		}
	} catch(int exception) {
		return exception;
	}
	return 0;
}
/*! \mainpage Marshmallow Duel: Percy's Return
*/
