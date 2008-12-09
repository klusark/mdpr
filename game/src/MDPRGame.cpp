#include <ClanLib/core.h>
#include <ClanLib/gl.h>
#include <ClanLib/display.h>
#include <iostream>
#include "MDPRGame.hpp"
#include "player.hpp"


void MDPRGame::run()
{
	Player *player = new Player;
	int t;

	static int T0     = 0;
	static int Frames = 0;
	float seconds, fps;
	CL_CollisionOutline outline("data/mdpr/sprites/player/run.PNG", 1);
	//generated.save("image.out");

	for(;;)
	{
		CL_Display::clear(CL_Color(0, 0, 0, 255));
		if( outline.point_inside( CL_Pointf(CL_Mouse::get_x(), CL_Mouse::get_y()) ))
		{
			std::cout<<"a";
		}



		player->update();
		player->draw(10, 10);
		outline.draw(0,0,CL_Color(0,255,0));

		CL_Display::flip();
		CL_System::sleep(1);
		CL_System::keep_alive();

		Frames++;
		t = CL_System::get_time();
		if (t - T0 >= 5000) {
			seconds = (t - T0) / 1000.0f;
			fps = Frames / seconds;
			std::cout<<Frames<<" frames in "<<seconds<<" seconds = "<<fps<<" FPS"<<std::endl;
			T0 = t;
			Frames = 0;
		
		}
	}
}
