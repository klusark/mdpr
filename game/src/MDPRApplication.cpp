#include <ClanLib/application.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/network.h>
#pragma warning(push, 3)
#include <ClanLib/gui.h>
#pragma warning(pop)
#include "MDPRApplication.hpp"
#include "MDPRGame.hpp"

MDPRApplication Application;
int MDPRApplication::main(int, char **)
{
	CL_ConsoleWindow console("Marshmallow Duel: Percy's Return Console");
	console.redirect_stdio();
	try {
		// CL initialization functions
		// These must be called or CL functions will not work
		// Also, SetupCore must be init()'ed first and denit()'ed last
		CL_SetupGL setupGL;
		CL_SetupCore setupCore;
		CL_SetupDisplay setupDisplay;
		CL_SetupNetwork setupNetwork;
		CL_SetupGUI setupGui;


		// Set display mode
		CL_DisplayWindow window("Marshmallow Duel: Percy's Return", 320, 200);
		
		CL_Slot slot_quit = window.sig_window_close().connect(this, &MDPRApplication::onWindowClose);
		
		MDPR.run();

		

	} catch (CL_Error err) {
		std::cout << "Exception caught: " << err.message.c_str() << std::endl;

		// Display console close message and wait for a key
		console.display_close_message();
	}
	// CL deinitialization functions
	CL_SetupGL::deinit();
	CL_SetupDisplay::deinit();
	CL_SetupCore::deinit();
	//network::destoryNetwork();
	return 0;
}

void MDPRApplication::onWindowClose()
{
	MDPR.onWindowClose();

}