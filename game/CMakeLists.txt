project( game )

set(SOURCES 
  src/engine.cpp
  src/MDPRApplication.cpp
  src/MDPRGame.cpp
  src/network/networkClient.cpp
  src/network/networkServer.cpp
  src/sprite/genericSprite.cpp
  src/sprite/imageManager.cpp
  src/sprite/player.cpp
  src/sprite/spriteManager.cpp
  src/menu/menuGeneric.cpp
  src/menu/menuMain.cpp
  src/menu/menuManager.cpp
  src/menu/menuOptions.cpp
  src/menu/menuProfile.cpp
  src/engine.hpp
  src/MDPRGame.hpp
  src/network/networkClient.hpp
  src/network/networkServer.hpp
  src/network/packets.hpp
  src/sprite/genericSprite.hpp
  src/sprite/imageManager.hpp
  src/sprite/player.hpp
  src/sprite/spriteManager.hpp
  src/menu/menuGeneric.hpp
  src/menu/menuMain.hpp
  src/menu/menuManager.hpp
  src/menu/menuOptions.hpp
  src/menu/menuProfile.hpp
)

include_directories( 
  ../../include
)

add_definitions( 
  -DSFML_DYNAMIC
)

add_executable( game ${SOURCES} )

target_link_libraries( game sfml-graphics sfml-window sfml-system boost_system-gcc43-mt-1_35 boost_thread-gcc43-mt-1_35 boost_program_options-gcc43-mt-1_35 )