#ifndef menuProfile_hpp
#define menuProfile_hpp

#include "menuGeneric.hpp"

class menuProfile : public menuGeneric
{
public:
	menuProfile(menuManager *menu, CL_StyleManager &style, std::string const &resourceLocation);
	~menuProfile();
};

#endif
