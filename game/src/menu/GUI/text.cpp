#include <string>
#include "text.hpp"

namespace GUI
{
	text::text(std::string sting)
	{
		boost::shared_ptr<sf::Drawable> newDrawable(new sf::String);
		drawable = newDrawable;

		dynamic_cast<sf::String *>(drawable.get())->SetText(sting);
	}

	text::~text()
	{
	}

	void text::update()
	{
	}

}
