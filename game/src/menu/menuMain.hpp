#ifndef menuMain_hpp
#define menuMain_hpp

#include "menuGeneric.hpp"

class menuMain : public menuGeneric
{
public:
	menuMain(sf::RenderWindow &App);
	~menuMain();
	static void toThis();

	gcn::Label label;


};

#endif // ifndef menuMain_hpp
