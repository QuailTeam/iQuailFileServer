cmake_minimum_required (VERSION 3.1)

add_library (common STATIC
	    Protocol.cpp
	    Network.cpp
	    FileManager.cpp
	    )
