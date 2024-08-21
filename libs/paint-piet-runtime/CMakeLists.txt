# file(GLOB SOURCES src/*.c)
find_package(PNG)
set(SOURCES src/colormatrix.c src/piet-commands.c src/utils.c src/pointer.c)
add_library(paint-piet-runtime SHARED ${SOURCES})
target_link_libraries(paint-piet-runtime ${PNG_LIBRARIES} logger)
target_include_directories(paint-piet-runtime PRIVATE ${PNG_INCLUDE_DIRS})

