#ifndef enumeration_hpp
#define enumeration_hpp

enum spriteTypes
{
	player,
	platform,
	bubble,
	selectionarea,
};

enum keys
{
	keyDown,
	keyUp,
	keyLeft,
	keyRight,
	keyAction,
};

enum errorIDs
{
	nameInUse,
};

enum spriteStates
{
	alive,
	spawning,
	dead,
};

#endif // #ifndef enumeration_hpp