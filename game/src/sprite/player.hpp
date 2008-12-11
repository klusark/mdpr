#ifndef player_hpp
#define player_hpp
#if _MSC_VER > 1000
#pragma once
#endif

#include <ClanLib/display.h>

class Player : public CL_Sprite
{
public:
	Player();
	~Player();
	CL_Sprite *run;
};

#endif
