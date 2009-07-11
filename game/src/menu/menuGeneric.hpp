#ifndef menuGeneric_hpp
#define menuGeneric_hpp

#include <Poco/SharedPtr.h>

#include <vector>

#include <guichan.hpp>
#include <guichan/sfml/sfmlgraphics.hpp>
#include <guichan/sfml/sfmlinput.hpp>
#include <guichan/sfml/sfmlimageloader.hpp>
#include <guichan/sfml/sfmlfont.hpp>

class MenuGeneric
	:	public gcn::Gui, 
		public gcn::ActionListener
{
public:
	MenuGeneric(sf::RenderWindow &App);
	~MenuGeneric();
	virtual void onChange();
	gcn::SFMLGraphics	graphics;
	gcn::SFMLInput		input;
	gcn::Container		top;
	void action(const gcn::ActionEvent &actionEvent);
	virtual void logic();

};

#endif //ifndef menuGeneric_hpp
