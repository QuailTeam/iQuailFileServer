cmake_minimum_required (VERSION 2.6)

add_executable(iQuailServer main.cpp)
target_link_libraries(iQuailServer ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
