#ifndef text_hpp
#define text_hpp

#include <SFML/Graphics.hpp>
#include "widget.hpp"

namespace GUI
{
	class text : public widget
	{
	public:
		text();
		~text();
		void draw();
		virtual void update();

	};
}


#endif //ifndef text_hpp
