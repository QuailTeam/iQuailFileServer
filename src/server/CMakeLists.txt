cmake_minimum_required (VERSION 3.1)

add_executable(iQuailServer
		main.cpp
		Server.cpp
		SFileManager.cpp
		CommandManager.cpp
		CmdGetFile.cpp
		CmdVersion.cpp
		CmdLs.cpp
		CmdNbrFiles.cpp
		PatchManager.cpp
		)

target_link_libraries(iQuailServer idiff common ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
