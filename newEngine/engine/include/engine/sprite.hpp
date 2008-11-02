#ifndef sprite_hpp
#define sprite_hpp
namespace engine
{
	class Sprite
	{
	public:
		EngineLib Sprite();
		virtual EngineLib ~Sprite();
		virtual EngineLib void update();
		const char *name;
	};
}
#endif