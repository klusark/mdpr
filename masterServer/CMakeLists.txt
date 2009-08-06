project(masterServer)

set(SOURCES
	src/networkMasterServer.cpp
	src/networkMasterServer.hpp
	../game/src/network/packets.hpp
)

include_directories( 
	../game/src
)


add_executable(masterServer ${SOURCES})

set(LINKFILES

)

target_link_libraries(masterServer ${LINKFILES})
