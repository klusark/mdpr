#ifndef genericPowerUp_hpp
#define genericPowerUp_hpp

#include <boost/shared_ptr.hpp>

class genericSprite;

class genericPowerUp
{
public:
	genericPowerUp(genericSprite *owner);
	~genericPowerUp();
	virtual void onActionKey();
	virtual void update();

	genericSprite *owner;
};

#endif // ifndef genericPowerUp_hpp
