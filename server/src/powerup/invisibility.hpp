#ifndef invisibility_hpp
#define invisibility_hpp

#include "genericPowerUp.hpp"

class Invisibility : public genericPowerUp
{
public:
	Invisibility(GenericSprite *owner);
	~Invisibility();	
	void onActionKey();
	void update();

};

#endif // #ifndef invisibility_hpp
