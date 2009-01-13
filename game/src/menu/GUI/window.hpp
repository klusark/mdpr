#ifndef window_hpp
#define window_hpp

#include "widget.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

namespace GUI
{
	class window
	{
		public:
		window(unsigned short width, unsigned short height, float x = 0, float y = 0);
		~window();
		void addWidget(widget newWidget);
		void draw();
		typedef std::vector<widget> widgetContainter;
		widgetContainter widgets;
		unsigned short width, height;
		sf::Shape rect;
	};
}


#endif //ifndef window_hpp
