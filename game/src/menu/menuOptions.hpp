#ifndef menuOptions_hpp
#define menuOptions_hpp

#include "menuGeneric.hpp"
#include "filteredTextField.hpp"

class menuOptions : public MenuGeneric
{
public:
	menuOptions(sf::RenderWindow &App);
	~menuOptions();
	static void toThis();

	void action(const gcn::ActionEvent &actionEvent);

	FilteredTextField textResWidth;
	FilteredTextField textResHeight;
	gcn::Label labelResWidth;
	gcn::Label labelResHeight;
	gcn::Label labelFullScreen;
	gcn::Label labelVsync;
	gcn::CheckBox fullScreen;
	gcn::CheckBox vsync;

	gcn::Button saveButton;

};

#endif // #ifndef menuOptions_hpp
