#ifndef menuServerBrowser_hpp
#define menuServerBrowser_hpp

#include "menuGeneric.hpp"

class menuServerBrowser : public menuGeneric
{
public:
	menuServerBrowser(sf::RenderWindow &App);
	~menuServerBrowser();
	static void toThis();
	//void action(const gcn::ActionEvent &actionEvent);


};

#endif // ifndef menuServerBrowser_hpp
