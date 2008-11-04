#ifndef player_hpp
#define player_hpp
class Player : public engine::Sprite, public engine::Animation, public engine::Movement, public engine::Mass, public engine::Collision, public engine::Input
{
public:
	Player(const char *name);
	~Player();
	void update();
	void test();
};
#endif
