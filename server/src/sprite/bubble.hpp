#ifndef bubble_hpp
#define bubble_hpp

#include "genericSprite.hpp"
#include "powerup.hpp"
#include "powerup/powerUpManager.hpp"

class Bubble : public GenericSprite
{
public:
	Bubble(const std::string &name);
	~Bubble();
	void update();

	GenericSprite::collidesWithContainer getCollidesWith();
	PowerUp powerup;
	
};

#endif // #ifndef bubble_hpp
