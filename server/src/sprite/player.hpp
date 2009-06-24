#ifndef player_hpp
#define player_hpp

#include "genericSprite.hpp"
#include "enumerations.hpp"

class Player : public genericSprite
{
public:
	Player(const std::string &name);
	~Player();
	void update();
	void crouchingFinish();
	void rollingFinish();
	void death(unsigned short cause); 

	bool keyMap[keyAction+1];
	bool keyMapTwo[keyAction+1];
	//keysContainter keyMap;
	bool rolling, running, crouching, idle, jumpingUp;
	float velocity;

	static const unsigned short runSpeed = 50;
	
};

#endif // #ifndef player_hpp
