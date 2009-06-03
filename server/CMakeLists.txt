project( server )

set(SOURCES
	src/main.cpp
	../game/src/sprite/genericSprite.cpp
	../game/src/sprite/genericSprite.hpp
	../game/src/network/networkServer.cpp
	../game/src/network/networkServer.hpp
	../game/src/network/packets.hpp
	../game/src/sprite/spriteManager.cpp
	../game/src/sprite/spriteManager.hpp
	../game/src/sprite/spriteCollision.cpp
	../game/src/sprite/spriteCollision.hpp
	../game/src/sprite/player.cpp
	../game/src/sprite/player.hpp
	../game/src/sprite/bubble.cpp
	../game/src/sprite/bubble.hpp
	../game/src/sprite/powerup.cpp
	../game/src/sprite/powerup.hpp
	../game/src/sprite/platform.cpp
	../game/src/sprite/platform.hpp
)

include_directories( 
	../game/src
)

add_definitions( 
	-DSERVER
)

add_executable( server ${SOURCES} )
FIND_PACKAGE( Boost 1.35 COMPONENTS system program_options thread)
set(LINKFILES
	optimized sfml-graphics
	debug sfml-graphics-d
	optimized sfml-window
	debug sfml-window-d
	optimized sfml-system
	debug sfml-system-d
	${Boost_LIBRARIES}
)

target_link_libraries(server ${LINKFILES})
