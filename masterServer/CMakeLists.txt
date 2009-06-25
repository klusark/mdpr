project(masterServer)

set(SOURCES
	src/main.cpp
	src/networkMasterServer.cpp
	src/networkMasterServer.hpp
	../game/src/network/packets.hpp
)

include_directories( 
	../game/src
)


add_executable(masterServer ${SOURCES})
FIND_PACKAGE(Boost 1.37 COMPONENTS system thread)
set(LINKFILES
	${Boost_LIBRARIES}
)

target_link_libraries(masterServer ${LINKFILES})
