#ifndef widget_hpp
#define widget_hpp

#include <SFML/Graphics.hpp>

namespace GUI
{
	class widget
	{
	public:
		widget();
		~widget();
		void draw();
		virtual void update();

	protected:
		sf::Shape shape;
		sf::IntRect rect;
		enum curveLocation
		{
			topRight,
			topLeft,
			bottomLeft,
			bottomRight,
		};
		void makeCurve(float x, float y, float radius, sf::Color color, curveLocation location);


	};
}


#endif //ifndef widget_hpp
