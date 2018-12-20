cmake_minimum_required (VERSION 2.6)

project(iQuailServer)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
find_package(Threads)
find_package(Boost 1.68.0 REQUIRED system)
subdirs(src)
subdirs(test_client)
