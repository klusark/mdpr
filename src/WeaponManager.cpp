extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "WeaponManager.hpp"

WeaponManager::WeaponManager()
{
	//lua_register( luaState, "addNPC", l_addNPC );

	//luaL_dofile(luaState, "./weapons/gun.lua");
}

WeaponManager::~WeaponManager()
{
}

/*int l_addNPC( lua_State* luaVM)
{
   printf("%s\n",lua_tostring(luaVM, -1));
   lua_pushnumber( luaVM, 0 );
   return 1;
}*/