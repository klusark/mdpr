#ifndef grenade_hpp
#define grenade_hpp

#include "genericPowerUp.hpp"

class Grenade : public genericPowerUp
{
public:
	Grenade(GenericSprite *owner);
	~Grenade();	
	void onActionKey();
	void update();

};

#endif // #ifndef mine_hpp
