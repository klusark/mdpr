#ifndef menuGeneric_hpp
#define menuGeneric_hpp

#include <boost/shared_ptr.hpp>

#include <vector>

#include "menuManager.hpp"
#include "GUI/widget.hpp"

class menuGeneric
{
public:
	menuGeneric();
	~menuGeneric();
	virtual void update();

	void addWidget(boost::shared_ptr<GUI::widget> newWidget);

	typedef std::vector<boost::shared_ptr<GUI::widget> > widgetContainer;
	widgetContainer widgets;


};

#endif //ifndef menuGeneric_hpp
