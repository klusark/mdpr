project( game )

set(SOURCES 
  src/MDPRGame.cpp
  src/MDPRGame.hpp
  src/crc.cpp
  src/crc.hpp
  src/network/networkClient.cpp
  src/network/networkServer.cpp
  src/network/networkClient.hpp
  src/network/networkServer.hpp
  src/network/packets.hpp
  src/sprite/genericSprite.cpp
  src/sprite/imageManager.cpp
  src/sprite/spriteManager.cpp
  src/sprite/genericSprite.hpp
  src/sprite/imageManager.hpp
  src/sprite/player.cpp
  src/sprite/player.hpp
  src/sprite/platform.cpp
  src/sprite/platform.hpp
  src/sprite/spriteCollision.cpp
  src/sprite/spriteCollision.hpp  
  src/sprite/spriteManager.hpp
  src/menu/menuGeneric.hpp
  src/menu/menuMain.hpp
  src/menu/menuManager.hpp
  src/menu/menuOptions.hpp
  src/menu/menuProfile.hpp
  src/menu/menuGeneric.cpp
  src/menu/menuMain.cpp
  src/menu/menuManager.cpp
  src/menu/menuOptions.cpp
  src/menu/menuProfile.cpp
  src/menu/GUI/window.cpp
  src/menu/GUI/window.hpp
  src/menu/GUI/clickable.cpp
  src/menu/GUI/clickable.hpp
  src/menu/GUI/button.cpp
  src/menu/GUI/button.hpp
  src/menu/GUI/widget.cpp
  src/menu/GUI/widget.hpp

)

include_directories( 
  ../../include
)

add_definitions( 
  -DSFML_DYNAMIC
)

add_executable( game ${SOURCES} )

SET(Boost_USE_MULTITHREAD ON)

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

target_link_libraries( game ${LINKFILES} )
