#include "widget.hpp"
#include "window.hpp"
#include "clickable.hpp"
#include "listBox.hpp"
#include "../../MDPRGame.hpp"

namespace GUI
{
	listBox::listBox()
		:	widget(),
			clickable(rect),
			suroundingBox(sf::IntRect(100,100,300,300), sf::Color(255,0,255,255))
	{
	}

	listBox::~listBox()
	{
	}

	void listBox::draw()
	{
		MDPR->App.Draw(*suroundingBox.drawable.get());
	}

}
