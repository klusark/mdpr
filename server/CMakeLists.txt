project( server )

set(SOURCES
	src/main.cpp

	../game/src/helpers.cpp
	../game/src/helpers.hpp

	src/network/networkServer.cpp
	src/network/networkServer.hpp
	../game/src/network/packets.hpp

	src/powerup/gun.cpp
	src/powerup/gun.hpp
	src/powerup/powerUpManager.cpp
	src/powerup/powerUpManager.hpp
	src/powerup/genericPowerUp.cpp
	src/powerup/genericPowerUp.hpp

	src/sprite/genericSprite.cpp
	src/sprite/genericSprite.hpp
	src/sprite/spriteManager.cpp
	src/sprite/spriteManager.hpp
	src/sprite/spriteCollision.cpp
	src/sprite/spriteCollision.hpp
	src/sprite/player.cpp
	src/sprite/player.hpp
	src/sprite/effect.cpp
	src/sprite/effect.hpp
	src/sprite/bubble.cpp
	src/sprite/bubble.hpp
	src/sprite/powerup.cpp
	src/sprite/powerup.hpp
	src/sprite/platform.cpp
	src/sprite/platform.hpp
	src/sprite/animation.cpp
	src/sprite/animation.hpp
	src/sprite/effectManager.cpp
	src/sprite/effectManager.hpp
	src/sprite/selectionArea.cpp
	src/sprite/selectionArea.hpp
)

include_directories( 
	../game/src
	src
)

add_definitions( 
	-DSERVER
)

add_executable(server ${SOURCES})
FIND_PACKAGE( Boost 1.35 COMPONENTS system program_options thread)
set(LINKFILES
	optimized sfml-system
	debug sfml-system-d
	${Boost_LIBRARIES}
)

target_link_libraries(server ${LINKFILES})
