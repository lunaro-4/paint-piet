
# find_package(GTK)
pkg_check_modules(GTK REQUIRED gtk4)
add_executable(gui gui.c)
target_link_libraries(gui ${GTK_LIBRARIES} logger)
target_include_directories(gui PRIVATE ${GTK_INCLUDE_DIRS})
add_compile_options(${GTK_CFLAGS_OTHER})
