list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
project(paint-piet LANGUAGES C)
set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")
include(CTest)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
cmake_minimum_required()
INCLUDE( FindPkgConfig )
# find_package(PkgConfig REQUIRED)
pkg_check_modules(PNG REQUIRED libpng)

include_directories(${PNG_INCLUDE_DIRS})
link_directories (${PNG_LIBRARY_DIRS})

enable_testing()

add_subdirectory(tests)
add_subdirectory(src)
# set(CMAKE_CTEST_ARGUMENTS --output-on-falure)



