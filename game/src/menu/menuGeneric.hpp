#ifndef menuGeneric_hpp
#define menuGeneric_hpp
#if _MSC_VER > 1000
#pragma once
#endif

class menuGeneric : public CL_GUIManager
{
public:
	menuGeneric(CL_StyleManager &style, std::string const &resourceLocation);
	~menuGeneric();
	void show();
private:
	CL_ComponentManager *componentManager;
};

#endif
