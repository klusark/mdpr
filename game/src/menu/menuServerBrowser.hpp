#ifndef menuServerBrowser_hpp
#define menuServerBrowser_hpp

#include "menuGeneric.hpp"
#include "serverListModel.hpp"

class menuServerBrowser : public menuGeneric
{
public:
	menuServerBrowser(sf::RenderWindow &App);
	~menuServerBrowser();
	static void toThis();
	//void action(const gcn::ActionEvent &actionEvent);
	gcn::ListBox serverListBox;
	ServerListModel serverListModel;

	gcn::Button connectButton;
	bool connectButtonDisplayed;

	void logic();

	void action(const gcn::ActionEvent &actionEvent);
};

#endif // ifndef menuServerBrowser_hpp
