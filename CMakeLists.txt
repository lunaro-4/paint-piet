list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
cmake_minimum_required()
project(paint-piet, LANGUAGES C)
INCLUDE( FindPkgConfig )
# find_package(PkgConfig REQUIRED)
pkg_check_modules(PNG REQUIRED libpng)

include_directories(${PNG_INCLUDE_DIRS})
link_directories (${PNG_LIBRARY_DIRS})

enable_testing()

add_subdirectory(tests)



add_executable(main main.c colormatrix.c custom_utils.c)
target_link_libraries (main ${PNG_LIBRARIES})
