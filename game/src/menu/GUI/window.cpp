#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

#include "window.hpp"
#include "button.hpp"
#include "../../MDPRGame.hpp"

namespace GUI
{
	window::window(sf::IntRect rect, sf::Color color)
	{
		//sf::Shape Rect = sf::Shape::Rectangle(x, y, x+width, x+height, sf::Color(0, 128, 128));
		boost::shared_ptr<sf::Drawable> newDrawable(new sf::Shape);
		drawable = newDrawable;
		
		drawable->SetX(float(rect.Top));
		drawable->SetY(float(rect.Left));

		float radius = 7.0f;
		float height = float(rect.Top);
		float width = float(rect.Left);

		makeCurve(0,		height, radius, color, bottomLeft);

		makeCurve(width,	height, radius, color, bottomRight);

		makeCurve(width,	0,		radius, color, topRight);

		makeCurve(0,		0,		radius, color, topLeft);

	}

	window::~window()
	{
	}
}
