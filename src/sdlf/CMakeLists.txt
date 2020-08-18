
if(WIN32)
	set(SDL2_INCLUDES "" CACHE DIRECTORY "SDL2 include directory")
	set(SDL2_LIBRARIES "" CACHE DIRECTORY "SDL2 library directory")
	file(GLOB SDL2_LIBRARIES
		${SDL2_LIBRARIES}/*.lib
	)
else()
	find_package(SDL2 REQUIRED)
endif()

add_library(sdlf STATIC
	"SDLF.hpp"
	"Window.hpp" "Window.cpp"
)

target_include_directories(sdlf PRIVATE
	${SDL2_INCLUDES}
)

target_link_libraries(sdlf PRIVATE
	${SDL2_LIBRARIES}
)