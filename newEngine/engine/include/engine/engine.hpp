#define EngineLib __declspec( dllexport )
namespace engine{
	extern EngineLib bool createWindow(int screenWidth, int screenHeight, int bitsPerPixel, const char * title);
}