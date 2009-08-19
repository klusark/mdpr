project(masterServer)

set(SOURCES
	src/networkMasterServer.cpp
	src/networkMasterServer.hpp
	../game/src/network/packets.hpp
	src/RequestHandleFunctions.cpp
	src/RequestHandleFunctions.hpp
	
	src/RequestHandler.cpp
	src/RequestHandler.hpp
	
	src/RequestHandlerFactory.cpp
	src/RequestHandlerFactory.hpp
)

include_directories( 
	../game/src
)


add_executable(masterServer ${SOURCES})

set(LINKFILES)

target_link_libraries(masterServer ${LINKFILES})
