#ifndef button_hpp
#define button_hpp

#include "clickable.hpp"
#include "widget.hpp"

namespace GUI
{
	class button : public widget, clickable
	{
	public:
		button();
		~button();

	};
}


#endif //ifndef button_hpp
