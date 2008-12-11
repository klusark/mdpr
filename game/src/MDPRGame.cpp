#include <ClanLib/core.h>
#include <ClanLib/gl.h>
#include <ClanLib/display.h>
#pragma warning(push, 3)
#include <ClanLib/gui.h>
#include <ClanLib/guistylesilver.h>
#pragma warning(pop)
#include <iostream>

#include "MDPRGame.hpp"
#include "sprite/player.hpp"
#include "network/network.hpp"
#include "menu/menuManager.hpp"

MDPRGame::MDPRGame()
{
	quit = false;

}

MDPRGame::~MDPRGame()
{
	
}

void MDPRGame::run()
{
	Player *player = new Player;
	int t;

	static int T0     = 0;
	static int Frames = 0;
	float seconds, fps;
	//CL_PixelBuffer test = player->get_frame_surface(player->get_current_frame()).draw(100,100);
	//CL_CollisionOutline outline(test);
	//outline.save("image.out");

	


	Network network;
	menuManager menu;

	while(!quit)
	{
		CL_Display::clear(CL_Color::black);
		menu.update();
/*		if( outline.point_inside( CL_Pointf(CL_Mouse::get_x(), CL_Mouse::get_y()) ))
		{
			std::cout<<"a";
		}*/
		//player->get_frame_surface(player->get_current_frame()).draw(100,100);



		player->update();
		player->draw(10, 10);
//		outline.draw(0,0,CL_Color(0,255,0));

		CL_Display::flip();
		CL_System::sleep(1);
		network.update();
		CL_System::keep_alive();

		Frames++;
		t = CL_System::get_time();
		if (t - T0 >= 5000) {
			seconds = (t - T0) / 1000.0f;
			fps = Frames / seconds;
			std::cout << Frames << " frames in " << seconds << " seconds = " << fps << " FPS" << std::endl;
			T0 = t;
			Frames = 0;
		
		}
	}
}
void MDPRGame::onWindowClose()
{
	quit = true;
	
}
