#ifndef graphics_hpp
#define graphics_hpp
#include <string>
#include <map>
#include "dataTypes.hpp"
namespace engine{
	namespace graphics{
		extern std::map<std::string, unsigned int> textures;
		EngineLib bool loadImage(char *ext, char *path, char *images, ...);
		extern EngineLib void drawTexturedQuad(Rect rect, unsigned int texture);
	}
}
#endif
