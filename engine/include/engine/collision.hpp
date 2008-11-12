#ifndef collision_hpp
#define collision_hpp
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
	}
}
#endif
