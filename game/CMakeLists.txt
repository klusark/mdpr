project(game)

set(SOURCES 
	src/MDPRGame.cpp
	src/MDPRGame.hpp
	
	src/network/networkClient.cpp
	src/network/networkClient.hpp
	src/network/packets.hpp
	
	src/menu/menuManager.hpp
	src/menu/menuManager.cpp

	src/sprite/clientSprite.cpp
	src/sprite/clientSprite.hpp
	src/sprite/clientSpriteManager.cpp
	src/sprite/clientSpriteManager.hpp
	
	src/profile/Profile.cpp
	src/profile/Profile.hpp
	src/profile/ProfileManager.cpp
	src/profile/ProfileManager.hpp

	src/helpers.cpp
	src/helpers.hpp
)

include_directories( 
	src
)

add_definitions( 
	-DSFML_DYNAMIC
	-D_CRT_SECURE_NO_WARNINGS
	-DNOMINMAX
)

add_executable(game ${SOURCES})



set(LINKFILES
	optimized	sfml-graphics
	debug 		sfml-graphics-d
	optimized 	sfml-window
	debug 		sfml-window-d
	optimized 	sfml-system
	debug		sfml-system-d
	optimized 	CEGUIBase
	debug 		CEGUIBase_d
	optimized 	OpenGlGUIRenderer
	debug 		OpenGlGUIRenderer_d
)

target_link_libraries( game ${LINKFILES} )
