cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif()

find_package(Threads)
find_package(Boost 1.62.0 REQUIRED system filesystem)

include_directories(common)
include_directories(idiff/include)

subdirs(idiff)
subdirs(common)
subdirs(server)
subdirs(client)
