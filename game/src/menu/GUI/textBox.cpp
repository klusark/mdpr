#include <boost/bind.hpp>
#include "textBox.hpp"
#include "../../MDPRGame.hpp"
#include <SFML/Graphics.hpp>

namespace GUI
{
	textBox::textBox()
		:	widget(),
			textArea(60, 20, 100, 300, sf::Color(0,0,0,255)),
			clickable(textArea.rect)
	{
		text.SetX(100);
		text.SetY(300);
		text.SetText("test");
		text.SetSize(15.0f);
		onDown.connect(boost::bind(&textBox::mouseDown, this));
	}

	textBox::~textBox()
	{
	}

	void textBox::mouseDown()
	{
	}
	
	void textBox::draw()
	{
		MDPR->App.Draw(*textArea.drawable.get());
		MDPR->App.Draw(text);
	}

	void textBox::update()
	{
		clickable::update();
	}

}
