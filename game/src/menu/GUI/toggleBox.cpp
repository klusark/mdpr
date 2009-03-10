#ifndef toggleBox_hpp
#define toggleBox_hpp

#include "widget.hpp"
#include "clickable.hpp"
#include "window.hpp"

namespace GUI
{
	class toggleBox : public widget, public clickable
	{
	public:
		toggleBox();
		~toggleBox();
		void draw();

		sf::Shape box;
		sf::Shape innerBox;
		bool toggled;

	};
}
#endif //ifndef toggleBox_hpp