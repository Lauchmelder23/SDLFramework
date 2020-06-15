add_library(sdlf STATIC
	"SDLF.hpp"
	"Window.hpp" "Window.cpp"
)

target_include_directories(sdlf PRIVATE
	"${CMAKE_SOURCE_DIR}/3rdparty/include/SDL"
	"maths"
)

target_link_libraries(sdlf PRIVATE
	"${CMAKE_SOURCE_DIR}/3rdparty/lib/SDL2.lib"
	"${CMAKE_SOURCE_DIR}/3rdparty/lib/SDL2main.lib"
)