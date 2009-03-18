#include "button.hpp"

namespace GUI
{
	button::button(sf::IntRect newRect)
		:	widget(),
			clickable(rect)			
	{
		rect = newRect;
		boost::shared_ptr<sf::Drawable> newDrawable(new sf::Shape);
		drawable = newDrawable;


		sf::Color color(255,128,0, 255);
		float radius = 5.0f;

		curvedBox(rect, radius, color);

	}

	button::~button()
	{
	}

	void button::update()
	{
		clickable::update();
	}

}
