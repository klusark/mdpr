project( server )

set(SOURCES 
	../game/src/sprite/genericSprite.cpp
	src/main.cpp
	../game/src/network/networkServer.cpp
	../game/src/sprite/player.cpp
	../game/src/sprite/spriteManager.cpp
	../game/src/sprite/genericSprite.hpp
	../game/src/network/networkServer.hpp
	../game/src/network/packets.hpp
	../game/src/sprite/player.hpp
	../game/src/sprite/spriteManager.hpp
)

include_directories( 
	../game/src
)

add_definitions( 
	-DSERVER
)

add_executable( server ${SOURCES} )
set(LINKFILES
	optimized sfml-graphics
	debug sfml-graphics-d
	optimized sfml-window
	debug sfml-window-d
	optimized sfml-system
	debug sfml-system-d
)

if (!MSVC)
	set(LINKFILES  ${LINKFILES}
		boost_system-gcc43-mt-1_35
		boost_thread-gcc43-mt-1_35 
		boost_program_options-gcc43-mt-1_35
	)
endif()

target_link_libraries(server ${LINKFILES})