#include "engineLib.hpp"
#include <map>
#include <string>
#include "graphics.hpp"
#include "engine.hpp"
#include "sdl/SDL_image.h"
#include <iostream>
#include <vector>

namespace engine{
	namespace graphics{
		unsigned int texture;
		std::map<std::string, unsigned int> textures;

		EngineLib bool loadImage(std::string ext, std::string path, std::vector<std::string> images)
		{

			unsigned int i;
			for (i=0; i < images.size(); ++i){
				std::string temp;
				temp = path;
				SDL_RWops *rwop;
				temp += images[i];
				temp += ext;
				
				rwop = SDL_RWFromFile(temp.c_str(), "rb");
				SDL_Surface *surface = IMG_Load_RW(rwop, 1);
				if (!surface){
					std::cout<<"Loading Image:" << IMG_GetError() << std::endl;
					throw 1;
				}
		        
				// Enable 2D Texture Support
				glGenTextures(1, &textures[images[i]]);
				glBindTexture(GL_TEXTURE_2D, textures[images[i]]);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

			}

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
