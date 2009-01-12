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

target_link_libraries( server sfml-graphics sfml-window sfml-system boost_system-gcc43-mt-1_35 boost_thread-gcc43-mt-1_35 boost_program_options-gcc43-mt-1_35 )
