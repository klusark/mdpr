#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

#include "window.hpp"
#include "button.hpp"
#include "../../MDPRGame.hpp"

namespace GUI
{
	window::window(sf::IntRect &rect, sf::Color color)
	{
		//sf::Shape Rect = sf::Shape::Rectangle(x, y, x+width, x+height, sf::Color(0, 128, 128));
		boost::shared_ptr<sf::Drawable> newDrawable(new sf::Shape);
		drawable = newDrawable;
		


		float radius = 7.0f;

		curvedBox(rect, radius, color);


	}

	window::~window()
	{
	}
}
