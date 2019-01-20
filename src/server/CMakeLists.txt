cmake_minimum_required (VERSION 3.1)

add_executable(iQuailServer
		main.cpp
		Server.cpp
		Session.cpp
		)

target_link_libraries(iQuailServer common ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
