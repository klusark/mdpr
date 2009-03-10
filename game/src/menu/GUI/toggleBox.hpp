#include <boost/bind.hpp>
#include "toggleBox.hpp"
#include "../../MDPRGame.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace GUI
{
	textBox::textBox()
		:	widget(),
			clickable(textArea.rect)
	{

	}

	textBox::~textBox()
	{
	}

	void textBox::draw()
	{
	}

}
