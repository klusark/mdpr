#ifndef player_hpp
#define player_hpp

#include <ClanLib/display.h>

class Player : public CL_Sprite
{
public:
	Player();
	~Player();
	CL_Sprite *run;
};

#endif
