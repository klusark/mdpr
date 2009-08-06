#ifndef hook_hpp
#define hook_hpp

#include "genericPowerUp.hpp"

class Hook : public genericPowerUp
{
public:
	Hook(GenericSprite *owner);
	~Hook();	
	void onActionKey();
	void update();

};

#endif // #ifndef hook_hpp
