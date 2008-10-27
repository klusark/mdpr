#include "engineLib.hpp"
#include "graphics.hpp"
#include <stdarg.h>
namespace engine{
	namespace graphics{

		EngineLib bool loadImage(char *images, ...)
		{

			va_list ap;
			int i = 0;

			va_start(ap, images);
			while (images != 0)
			{
				printf("%s",images);
				
				images = va_arg(ap, char *);
				++i;
			}

			va_end(ap);
			return true;
		}
	}
}