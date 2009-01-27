#include "text.hpp"
#include <iostream>
namespace GUI
{
	text::text()
	{
		boost::shared_ptr<sf::Drawable> newDrawable(new sf::String);
		drawable = newDrawable;

		dynamic_cast<sf::String *>(drawable.get())->SetText("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	}

	text::~text()
	{
	}

	void text::update()
	{
	}

}
