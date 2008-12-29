/*#include <ClanLib/application.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/network.h>
#pragma warning(push, 3)
#include <ClanLib/gui.h>
#pragma warning(pop)*/

#include <boost/program_options.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "MDPRGame.hpp"
//#include "MDPRApplication.hpp"

int main(int argc, char** argv)
{
	/*CL_ConsoleWindow console("Marshmallow Duel: Percy's Return Console");
	console.redirect_stdio();*/
	try {
		int animations;
		boost::program_options::options_description config("Configuration");
		config.add_options()("animations", boost::program_options::value<int>(&animations), "");

		boost::program_options::variables_map vm;

		boost::program_options::options_description configFileOptions;
		configFileOptions.add(config);
		

		std::ifstream ifs("test.txt");

		boost::program_options::store(parse_config_file(ifs, configFileOptions), vm);
		notify(vm);
		


		// Set display mode
		sf::RenderWindow App(sf::VideoMode(640, 400, 32), "Marshmallow Duel: Percy's Return");
		
		

		App.SetBackgroundColor(sf::Color(0, 0, 0));
			//CL_Slot slot_quit = window.sig_window_close().connect(this, &MDPRApplication::onWindowClose);
		MDPRGame MDPR(App);
		MDPR.run();



	//} catch (CL_Error error) {
	//	std::cout << "Exception caught: " << error.message.c_str() << std::endl;

		// Display console close message and wait for a key
	//	console.display_close_message();
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
		return false;
	}

	// CL deinitialization functions
	//CL_SetupGL::deinit();
	//CL_SetupDisplay::deinit();
	//CL_SetupCore::deinit();
	//network::destoryNetwork();
	
	return 0;
}

/*void MDPRApplication::onWindowClose()
{
	MDPR.onWindowClose();

}
*/
