cmake_minimum_required(VERSION 3.8)

project("SDLFramework")

set(ENABLE_EXAMPLE_PROJECT OFF CACHE BOOL "Build a simple example application")


add_subdirectory("src/sdlf")

if(ENABLE_EXAMPLE_PROJECT)
	add_subdirectory("src/example")
endif()