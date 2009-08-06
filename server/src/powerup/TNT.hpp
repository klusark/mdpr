#ifndef TNT_hpp
#define TNT_hpp

#include "genericPowerUp.hpp"

class TNT : public genericPowerUp
{
public:
	TNT(GenericSprite *owner);
	~TNT();	
	void onActionKey();
	void update();

};

#endif // #ifndef TNT_hpp
