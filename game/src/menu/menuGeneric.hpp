/*#ifndef menuGeneric_hpp
#define menuGeneric_hpp

#include <boost/shared_ptr.hpp>

#include "menuManager.hpp"

class menuManager;

class menuGeneric : public CL_GUIManager
{
public:
	menuGeneric(CL_StyleManager &style, std::string const &resourceLocation);
	~menuGeneric();
	void show();
protected:
	boost::shared_ptr<CL_ComponentManager> componentManager;
	CL_SlotContainer slots;

};

#endif
*/