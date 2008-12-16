#include <ClanLib/core.h>
#include <ClanLib/gl.h>
#include <ClanLib/display.h>
#pragma warning(push, 3)
#include <ClanLib/gui.h>
#include <ClanLib/guistylesilver.h>
#pragma warning(pop)
#include <iostream>

#include "MDPRGame.hpp"
//#include "sprite/player.hpp"
#include "network/network.hpp"
#include "menu/menuManager.hpp"
#include "sprite/spriteManager.hpp"

MDPRGame::MDPRGame()
{
	quit = false;

}

MDPRGame::~MDPRGame()
{

}

void MDPRGame::run()
{
	//Player *player = new Player;
	int t;

	static int T0     = 0;
	static int Frames = 0;
	float seconds, fps = 0;
	//CL_PixelBuffer test = player->get_frame_surface(player->get_current_frame()).draw(100,100);
	//CL_CollisionOutline outline(test);
	//outline.save("image.out");






	CL_ResourceManager resources("data/mdpr/gui/gui.xml", false);
	CL_Font font("fontMDPR", &resources);
	font.set_color(CL_Color::white);

	boost::shared_ptr<menuManager> tmpMenu(new menuManager(resources));
	menu = tmpMenu;
	menu->setActive(true);

	boost::shared_ptr<spriteManager> tmpSprite(new spriteManager);
	sprite = tmpSprite;

	sprite->setActive(true);
	std::cout<<sprite;
	boost::shared_ptr<Network> network(new Network);



	while(!quit)
	{
		CL_Display::clear(CL_Color::black);

		if (menu->isActive()){
			menu->update();
		}

;
//		outline.draw(0,0,CL_Color(0,255,0));

		network->update();

        if (sprite->isActive()){
			sprite->update();
			sprite->draw();
		}


		Frames++;
		t = CL_System::get_time();
		if (t - T0 >= 1000) {
			seconds = (t - T0) / 1000.0f;
			fps = Frames / seconds;
			//std::cout << Frames << " frames in " << seconds << " seconds = " << fps << " FPS" << std::endl;
			T0 = t;
			Frames = 0;
		}
		std::stringstream buf;
		buf << std::fixed << static_cast<int>(fps);
		std::string stringFPS = buf.str();

		font.draw(320-font.get_width(stringFPS), 0, stringFPS);

		CL_Display::flip();
		CL_System::sleep(2);

		CL_System::keep_alive();
	}
}
void MDPRGame::onWindowClose()
{
	quit = true;

}
