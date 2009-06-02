#ifndef menuGeneric_hpp
#define menuGeneric_hpp

#include <boost/shared_ptr.hpp>

#include <vector>

#include <guichan.hpp>
#include <guichan/sfml/sfmlgraphics.hpp>
#include <guichan/sfml/sfmlinput.hpp>
#include <guichan/sfml/sfmlimageloader.hpp>
#include <guichan/sfml/sfmlfont.hpp>

class menuGeneric
	:	public gcn::Gui
{
public:
	menuGeneric(sf::RenderWindow &App);
	~menuGeneric();
	virtual void onChange();
	gcn::Gui			gui;
	gcn::SFMLGraphics	graphics;
	gcn::SFMLInput		input;
	gcn::Container		top;

};

#endif //ifndef menuGeneric_hpp
