cmake_minimum_required (VERSION 3.1)
project(idiff VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(idiff SHARED
	src/bucket.c
	src/crc32.c
	src/helpers.c
	src/xdiff.c
)
set_target_properties(idiff PROPERTIES PUBLIC_HEADER include/libidiff.h)
target_include_directories(idiff PRIVATE .)
