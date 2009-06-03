#ifndef menuOptions_hpp
#define menuOptions_hpp

#include "menuGeneric.hpp"
#include "filteredTextField.hpp"
#include "button.hpp"

class menuOptions : public menuGeneric
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

	Button saveButton;


};

#endif // ifndef menuOptions_hpp
