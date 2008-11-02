extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "SDL/SDL_image.h"
#include "GameManager.hpp"
#include "WeaponManager.hpp"

WeaponManager::WeaponManager(GameManager *gm)
{
	/*this->gm = gm;
	lua_register(gm->luaState, "loadImages", &WeaponManager::loadImages);
	
	luaL_dofile(gm->luaState, "./weapons/gun.lua");
	lua_getglobal(gm->luaState, "use");
	lua_call(gm->luaState, 0, 0);
	*/

}

WeaponManager::~WeaponManager()
{
}

void WeaponManager::use()
{
}

/*int WeaponManager::loadImages(lua_State *luaState)
{
	//printf("%s\n",);
	std::string name = std::string(lua_tostring(luaState, -1));
	SDL_RWops *rwop;
	std::string file;
	file += "data/main/";
	file += name;
	file += ".png";
	rwop = SDL_RWFromFile(file.c_str(), "rb");
	gm->images[name] = IMG_LoadPNG_RW(rwop);
	if (!images[name])
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	SDL_FreeRW(rwop);
	flippedImages[name] = flipImage(images[name]);
	return 1;
}*/
