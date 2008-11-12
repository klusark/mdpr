#ifndef window_hpp
#define window_hpp
#include <string>
namespace engine{
	namespace window{
		extern bool isActive;
		extern EngineLib bool createWindow(int screenWidth, int screenHeight, int bitsPerPixel, std::string title, bool fullScreen);
		extern void windowResize(int width, int height);
		extern void draw();
	}
}
#endif
