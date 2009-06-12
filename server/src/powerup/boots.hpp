#ifndef boots_hpp
#define boots_hpp

#include "genericPowerUp.hpp"

class Boots : public genericPowerUp
{
public:
	Boots(genericSprite *owner);
	~Boots();	
	void onActionKey();
	void update();

};

#endif // #ifndef boots_hpp
