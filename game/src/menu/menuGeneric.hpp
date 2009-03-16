#ifndef menuGeneric_hpp
#define menuGeneric_hpp

#include <boost/shared_ptr.hpp>

#include <vector>

#include "GUI/widget.hpp"

class menuGeneric
{
public:
	menuGeneric();
	~menuGeneric();
	virtual void update();
	virtual void draw();
	virtual void onChange();

	void addWidget(boost::shared_ptr<GUI::widget> newWidget);

	typedef std::vector<boost::shared_ptr<GUI::widget> > widgetContainer;
	widgetContainer widgets;


};

#endif //ifndef menuGeneric_hpp
