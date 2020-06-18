add_library(sdlf STATIC
	"SDLF.hpp"
	"Window.hpp" "Window.cpp"
)

target_include_directories(sdlf PRIVATE
	"${PROJECT_SOURCE_DIR}/3rdparty/include/SDL"
)

target_link_libraries(sdlf PRIVATE
	"${PROJECT_SOURCE_DIR}/3rdparty/lib/SDL2.lib"
	"${PROJECT_SOURCE_DIR}/3rdparty/lib/SDL2main.lib"
)