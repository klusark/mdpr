project( game )

set(SOURCES 
	src/MDPRGame.cpp
	src/MDPRGame.hpp
	
	src/network/networkClient.cpp
	src/network/networkClient.hpp
	src/network/packets.hpp
	
	src/sprite/genericSprite.cpp
	src/sprite/spriteManager.cpp
	src/sprite/genericSprite.hpp
	src/sprite/player.cpp
	src/sprite/player.hpp
	src/sprite/bubble.cpp
	src/sprite/bubble.hpp
	src/sprite/powerup.cpp
	src/sprite/powerup.hpp
	src/sprite/platform.cpp
	src/sprite/platform.hpp
	src/sprite/spriteCollision.cpp
	src/sprite/spriteCollision.hpp  
	src/sprite/spriteManager.hpp
	src/sprite/animation.cpp
	src/sprite/animation.hpp
	src/sprite/selectionArea.cpp
	src/sprite/selectionArea.hpp
	
	src/powerup/powerupmanager.cpp
	src/powerup/powerupmanager.hpp
	src/powerup/genericPowerUp.cpp
	src/powerup/genericPowerUp.hpp
	src/powerup/gun.cpp
	src/powerup/gun.hpp
	
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
	src/menu/menuInGame.cpp
	src/menu/menuInGame.hpp
	src/menu/menuServerBrowser.cpp
	src/menu/menuServerBrowser.hpp
	src/menu/button.cpp
	src/menu/button.hpp
	src/menu/filteredTextField.cpp
	src/menu/filteredTextField.hpp
	
	src/helpers.cpp
	src/helpers.hpp
)

include_directories( 
	../../include
)

add_definitions( 
	-DSFML_DYNAMIC
	-D_CRT_SECURE_NO_WARNINGS
	-D_WIN32_WINNT=0x0501
)

add_executable( game ${SOURCES} )

SET(Boost_USE_MULTITHREAD ON)

FIND_PACKAGE( Boost 1.39 COMPONENTS system program_options thread signals)

set(LINKFILES
	optimized sfml-graphics
	debug sfml-graphics-d
	optimized sfml-window
	debug sfml-window-d
	optimized sfml-system
	debug sfml-system-d
	optimized guichan
	debug guichand
	optimized guichan_sfml
	debug guichan_sfmld
	${Boost_LIBRARIES}
)

target_link_libraries( game ${LINKFILES} )
