#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

#include "window.hpp"
#include "button.hpp"
#include "../../MDPRGame.hpp"

namespace GUI
{
	window::window(unsigned int width, unsigned int height, float x, float y, sf::Color color)
		:	width(width),
			height(height)
	{
		//sf::Shape Rect = sf::Shape::Rectangle(x, y, x+width, x+height, sf::Color(0, 128, 128));
		boost::shared_ptr<sf::Drawable> newDrawable(new sf::Shape);
		drawable = newDrawable;
		
		drawable->SetX(x);
		drawable->SetY(y);
		rect.Bottom = (int)y + height;
		rect.Top = (int)y;
		rect.Right = (int)x + width;
		rect.Left = (int)x;
		float radius = 7.0f;

		makeCurve(0,		height, radius, color, bottomLeft);

		makeCurve(width,	height, radius, color, bottomRight);

		makeCurve(width,	0,		radius, color, topRight);

		makeCurve(0,		0,		radius, color, topLeft);

	}

	window::~window()
	{
	}
}
