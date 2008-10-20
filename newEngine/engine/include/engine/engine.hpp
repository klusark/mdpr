#define EngineLib __declspec( dllexport )
namespace engine{
	namespace window{
		extern EngineLib bool createWindow(int screenWidth, int screenHeight, int bitsPerPixel, const char * title);
	}
}