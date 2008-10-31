#include <map>
#include <string>
#include "graphics.hpp"
#include "engine.hpp"
#include "sdl/sdl_image.h"
#include <stdarg.h>

namespace engine{
	namespace graphics{
		unsigned int texture;
		std::map<std::string, unsigned int> textures;
		EngineLib bool loadImage(char *ext, char *path, char *images, ...)
		{

			va_list ap;
			int i = 0;
			va_start(ap, images);
			while (images != 0)
			{
				char temp[64];
				strcpy (temp, path);
				SDL_RWops *rwop;
				strcat(temp, images);
				strcat(temp, ext);
				rwop = SDL_RWFromFile(temp, "rb");
				SDL_Surface *surface = IMG_LoadPNG_RW(rwop);
				if (!surface){
					printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
					return false;
				}
				SDL_FreeRW(rwop);
		        
				// Enable 2D Texture Support
				glGenTextures(1, &textures[images]);
				glBindTexture(GL_TEXTURE_2D, textures[images]);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

				images = va_arg(ap, char *);
				++i;
			}

			va_end(ap);
			return true;
		}

		EngineLib void drawTexturedQuad(Rect rect, unsigned int texture)
		{
			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_QUADS);
				//Top-left vertex (corner)
				glTexCoord2i(0, 0);
				glVertex2d(rect.x, rect.y);
				
				//top-right vertex (corner)
				glTexCoord2i(1, 0);
				glVertex2d(rect.x + rect.w, rect.y);
				
				//Bottom-right vertex (corner)
				glTexCoord2i(1, 1);
				glVertex2d(rect.x+rect.w, rect.y+rect.h);
				
				//bottom-left vertex (corner)
				glTexCoord2i(0, 1);
				glVertex2d(rect.x , rect.y+ rect.h);

			glEnd();


		}
	}
}
