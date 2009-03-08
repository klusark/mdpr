#ifndef text_hpp
#define text_hpp

#include <SFML/Graphics.hpp>
#include "widget.hpp"

namespace GUI
{
	class text : public widget
	{
	public:
		text(unsigned int width, unsigned int height, float x, float y, std::string sting);
		~text();
		void update();

	};
}


#endif //ifndef text_hpp
