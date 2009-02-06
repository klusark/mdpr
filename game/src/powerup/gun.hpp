#ifndef gun_hpp
#define gun_hpp

#include "genericPowerUp.hpp"

class Gun : public genericPowerUp
{
public:
	Gun(genericSprite *owner);
	~Gun();	
	void onActionKey();
	void update();
};

#endif // ifndef gun_hpp
