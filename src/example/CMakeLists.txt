add_executable(example_app 
	"main.cpp"
)

target_include_directories(example_app PRIVATE
	"${CMAKE_SOURCE_DIR}/src/sdlf"
	"${CMAKE_SOURCE_DIR}/3rdparty/include/SDL"
)

target_link_libraries(example_app PRIVATE
	sdlf
	"${CMAKE_SOURCE_DIR}/3rdparty/lib/SDL2.lib"
	"${CMAKE_SOURCE_DIR}/3rdparty/lib/SDL2main.lib"
)

add_custom_command(TARGET example_app POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/3rdparty/lib/SDL2.dll $<TARGET_FILE_DIR:example_app>
)