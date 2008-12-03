#ifndef engineAll_hpp
#define engineAll_hpp

#if defined(_WIN32) || defined(WIN32)
	#define EngineLib __declspec( dllexport )
#endif

#ifndef EngineLib
	#define EngineLib
#endif

#include "engine.hpp"
#include "window.hpp"
#include "graphics.hpp"
#include "dataTypes.hpp"
#include "sprite.hpp"
#include "spriteManager.hpp"
#include "spriteAnimation.hpp"
#include "spriteMovement.hpp"
#include "spriteMass.hpp"
#include "spriteCollision.hpp"
#include "spriteInput.hpp"
#include "collision.hpp"
#endif
