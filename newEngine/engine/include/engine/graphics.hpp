#include <string>
#include <map>

namespace engine{
	namespace graphics{
		extern std::map<std::string, unsigned int> textures;
		extern unsigned int texture;
		EngineLib bool loadImage(char *images, ...);
	}
}
