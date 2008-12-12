#ifndef menuGeneric_hpp
#define menuGeneric_hpp


#include "menuManager.hpp"
class menuManager;
class menuGeneric : public CL_GUIManager
{
public:
	menuGeneric(menuManager *menu, CL_StyleManager &style, std::string const &resourceLocation);
	~menuGeneric();
	void show();
protected:
	CL_ComponentManager *componentManager;
	CL_SlotContainer slots;
	menuManager *menu;

};

#endif
