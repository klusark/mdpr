#include "widget.hpp"
#include "../../MDPRGame.hpp"

namespace GUI
{
	widget::widget()
	{

	}

	widget::~widget()
	{
	}

	void widget::draw()
	{
		MDPR.App.Draw(rect);
	}

}
