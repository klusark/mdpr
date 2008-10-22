
namespace engine{
	namespace window{
		extern bool isActive;
		extern EngineLib bool createWindow(int screenWidth, int screenHeight, int bitsPerPixel, const char * title, bool fullScreen);
		extern void windowResize(int width, int height);
		extern void draw();
	}
}