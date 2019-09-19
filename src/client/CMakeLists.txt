cmake_minimum_required (VERSION 3.1)

add_executable(iQuailClient
		main.cpp
		Client.cpp
		CommandManager.cpp
		CmdGetFile.cpp
		CmdVersion.cpp
		CmdLs.cpp
		CmdNbrFiles.cpp)

target_link_libraries(iQuailClient common ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
