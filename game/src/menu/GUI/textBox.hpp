#ifndef textBox_hpp
#define textBox_hpp

#include "widget.hpp"
#include "clickable.hpp"
#include "window.hpp"

namespace GUI
{
	class textBox : public widget, public clickable
	{
	public:
		textBox();
		~textBox();
		void mouseDown();
		void draw();
		void update();
		void clicked();
		window textArea;
		sf::String text;
		sf::Shape position;
	};
}
#endif //ifndef textBox_hpp