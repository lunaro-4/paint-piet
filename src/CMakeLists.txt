add_executable(main main.c colormatrix.c custom_utils.c runtime.c piet-commands.c)
target_link_libraries (main ${PNG_LIBRARIES})
