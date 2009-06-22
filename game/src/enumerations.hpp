#ifndef enumeration_hpp
#define enumeration_hpp

enum spriteTypes
{
	playerType,
	platformType,
	bubbleType,
	selectionAreaType,
	effectType
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
	aliveState,
	spawningState,
	readyToSpawnState,
	deadState,
	dyingState,
};

enum connectionState
{
	connectingState,
	connectedState,
	idleState,
};

#endif // #ifndef enumeration_hpp