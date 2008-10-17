#ifndef WEAPONMANAGER_HPP
#define WEAPONMANAGER_HPP

class GameManager;
struct lua_State;

class WeaponManager
{
	public:
		WeaponManager(GameManager *gm);
		~WeaponManager();
		GameManager *gm;
		void use();
		//static int loadImages(lua_State *luaState);
};

#endif