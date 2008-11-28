#ifndef graphics_hpp
#define graphics_hpp
#include <string>
#include <map>
#include "dataTypes.hpp"
#include <vector>
namespace engine{
	namespace graphics{
		extern std::map<std::string, unsigned int> textures;
		extern EngineLib bool loadImage(std::string ext, std::string path, std::vector<std::string> images);
		extern EngineLib void drawTexturedQuad(Rect rect, unsigned int texture);
	}
}
#endif