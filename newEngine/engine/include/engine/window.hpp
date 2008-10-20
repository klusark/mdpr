
namespace engine{
	namespace window{
		extern EngineLib bool createWindow(int screenWidth, int screenHeight, int bitsPerPixel, const char * title, bool fullScreen);
		extern EngineLib void eventLoop();
		extern EngineLib void mainLoop();
	}
}