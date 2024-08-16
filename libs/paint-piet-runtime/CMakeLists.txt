# file(GLOB SOURCES src/*.c)
set(SOURCES src/colormatrix.c src/piet-commands.c src/utils.c src/pointer.c)
add_library(paint-piet-runtime.so ${SOURCES})
target_link_libraries(paint-piet-runtime.so ${PNG_LIBRARIES})
