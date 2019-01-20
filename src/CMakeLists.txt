cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Threads)
find_package(Boost 1.68.0 REQUIRED system)

include_directories(common)

subdirs(common)
subdirs(server)
subdirs(client)
