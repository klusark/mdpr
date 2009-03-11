#include <string>
#include "text.hpp"

namespace GUI
{
	text::text(unsigned int width, unsigned int height, float x, float y, std::string sting)
	{
		boost::shared_ptr<sf::Drawable> newDrawable(new sf::String);
		drawable = newDrawable;
		drawable->SetX(x);
		drawable->SetY(y);

		sf::String * myString = dynamic_cast<sf::String *>(drawable.get());
		myString->SetSize(float(height));

		myString->SetText(sting);
	}

	text::~text()
	{
	}

	void text::update()
	{
	}

}
