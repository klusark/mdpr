#include "Player.hpp"
#include "GameManager.hpp"
#include "SpriteManager.hpp"

bool running = true;
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
