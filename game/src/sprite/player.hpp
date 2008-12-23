#ifndef player_hpp
#define player_hpp

#include "genericSprite.hpp"

class Player : public genericSprite
{
public:
	Player(const std::string &name, bool server = false);
	~Player();
};

#endif
