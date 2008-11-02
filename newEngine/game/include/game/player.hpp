#ifndef player_hpp
#define player_hpp
#include "engine/engineAll.hpp"
class Player : public engine::Sprite, public engine::Animation, public engine::Movement
{
public:
	Player(const char *name);
	~Player();
	virtual void update();
	void test();
};
#endif
