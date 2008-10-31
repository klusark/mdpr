#ifndef sprite_hpp
#define sprite_hpp
namespace engine
{
	class EngineLib Sprite
	{
	public:
		Sprite();
		virtual ~Sprite();
		virtual void update();
	};
}
#endif