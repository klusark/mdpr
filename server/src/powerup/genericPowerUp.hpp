#ifndef genericPowerUp_hpp
#define genericPowerUp_hpp

#include <Poco/SharedPtr.h>

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
