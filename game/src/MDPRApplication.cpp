#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "MDPRGame.hpp"


int main(int argc, char** argv)
{

	try {

		// Set display mode
		sf::RenderWindow App(sf::VideoMode(640, 400, 32), "Marshmallow Duel: Percy's Return");
		
					
		MDPRGame MDPR(App);
		MDPR.run();

	}catch (std::exception& e){
		std::cout << "Exception: " << e.what() << "\n";
		return false;
	}

	
	return 0;
}
