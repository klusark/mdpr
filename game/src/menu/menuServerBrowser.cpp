#include "menuServerBrowser.hpp"
#include "menuGeneric.hpp"
#include "menuMain.hpp"
#include "menuManager.hpp"
#include "menuInGame.hpp"
#include "MDPRGame.hpp"


menuServerBrowser::menuServerBrowser(sf::RenderWindow &App)
	:	menuGeneric(App),
		connectButtonDisplayed(false)
{

	serverListBox.setDimension(gcn::Rectangle(50, 50, 200, 200));
	serverListBox.setListModel(&serverListModel);

	connectButton.setDimension(gcn::Rectangle(300, 300, 0, 0));
	connectButton.setCaption("Connect");
	connectButton.adjustSize();
	connectButton.addActionListener(this);
	connectButton.setActionEventId("connect");

	top.add(&serverListBox);

}

menuServerBrowser::~menuServerBrowser()
{
}

void menuServerBrowser::action(const gcn::ActionEvent &actionEvent)
{
	int selected = serverListBox.getSelected();
	if (actionEvent.getId() == "connect"){
		MDPR->myNetworkClient->connectToServer(MDPR->myNetworkClient->serverList[selected].entry);
		menuInGame::toThis();
	}
}

void menuServerBrowser::logic()
{
	int selected = serverListBox.getSelected();
	if (selected == -1){
		if (connectButtonDisplayed){
			top.remove(&connectButton);
			connectButtonDisplayed = false;
		}
		
	}else{
		if (!connectButtonDisplayed){
			top.add(&connectButton);
			connectButtonDisplayed = true;
		}

	}
	menuGeneric::logic();
}

void menuServerBrowser::toThis()
{
	menu->changeCurrentMenu("menuServerBrowser");
}
