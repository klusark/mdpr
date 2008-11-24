#ifndef collision_hpp
#define collision_hpp
#include "dataTypes.hpp"
namespace engine
{
	namespace collision
	{
		enum collisonDirections
		{
			up = 1,
			down,
			left,
			right,
			all = up|down|left|right,
		};
		void update();
		bool isCollided(Rect a, Rect b);
		bool isRightOf(Rect a, Rect b);
		bool isLeftOf(Rect a, Rect b);
		bool isUpOf(Rect a, Rect b);
		bool isDownOf(Rect a, Rect b);
	}
}
#endif
