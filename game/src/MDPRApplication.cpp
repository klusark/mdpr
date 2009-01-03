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
