#ifndef mine_hpp
#define mine_hpp

#include "genericPowerUp.hpp"

class Mine : public genericPowerUp
{
public:
	Mine(GenericSprite *owner);
	~Mine();	
	void onActionKey();
	void update();

};

#endif // #ifndef mine_hpp
