#ifndef death_hpp
#define death_hpp

#include "genericPowerUp.hpp"

class Death : public genericPowerUp
{
public:
	Death(genericSprite *owner);
	~Death();	
	void onActionKey();
	void update();

};

#endif // #ifndef death_hpp
