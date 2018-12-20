cmake_minimum_required (VERSION 3.1)

add_executable(iQuailClient main.cpp)

target_link_libraries(iQuailClient ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
