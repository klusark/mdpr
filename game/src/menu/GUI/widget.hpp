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

		private:
		sf::Shape rect;


	};
}


#endif //ifndef widget_hpp
