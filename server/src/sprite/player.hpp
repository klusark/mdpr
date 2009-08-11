#ifndef player_hpp
#define player_hpp

#include "genericSprite.hpp"
#include "enumerations.hpp"

class Player : public GenericSprite
{
public:
	Player(const std::string &name);
	~Player();
	void update();
	void crouchingFinish();
	void rollingFinish();
	void death(unsigned short cause);

	void onAnimationFinish();

	static GenericSprite::collidesWithContainer colidesWith;
	GenericSprite::collidesWithContainer getCollidesWith() const {return colidesWith;};

	bool keyMap[keyAction+1];
	bool keyMapTwo[keyAction+1];
	bool rolling, running, crouching, idle, jumpingUp;
	float velocity;

	static const unsigned short runSpeed = 50;
	
};

#endif // #ifndef player_hpp
