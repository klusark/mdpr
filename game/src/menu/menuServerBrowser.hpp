#ifndef menuServerBrowser_hpp
#define menuServerBrowser_hpp

#include "menuGeneric.hpp"

class menuServerBrowser : public menuGeneric
{
public:
	menuServerBrowser(sf::RenderWindow &App);
	~menuServerBrowser();
	static void toThis();


};

#endif // ifndef menuServerBrowser_hpp
