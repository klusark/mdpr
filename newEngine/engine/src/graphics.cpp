#include <map>
#include <string>
#include "engineLib.hpp"
#include "graphics.hpp"
#include "sdl/sdl_image.h"
#include <stdarg.h>

namespace engine{
	namespace graphics{
		unsigned int texture;
		std::map<std::string, unsigned int> textures;
		EngineLib bool loadImage(char *images, ...)
		{

			va_list ap;
			int i = 0;
			va_start(ap, images);
			while (images != 0)
			{
				char temp[80];
				strcpy (temp, images);
				SDL_RWops *rwop;
				strcat(temp, ".png");
				rwop = SDL_RWFromFile(temp, "rb");
				SDL_Surface *surface = IMG_LoadPNG_RW(rwop);
				if (!surface)
					printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
				SDL_FreeRW(rwop);
		        
				// Enable 2D Texture Support
				glGenTextures(1, &textures[images]);
				glBindTexture(GL_TEXTURE_2D, textures[images]);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

				printf("%i",textures[images]);
				images = va_arg(ap, char *);
				++i;
			}

			va_end(ap);
			return true;
		}
	}
}