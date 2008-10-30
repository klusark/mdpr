#include <string>
#include <map>

namespace engine{
	namespace graphics{
		extern std::map<std::string, unsigned int> textures;
		EngineLib bool loadImage(char *ext, char *path, char *images, ...);
	}
}
