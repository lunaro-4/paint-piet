list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
# cmake_minimum_required(VERSION 3.22)
project(paint-piet LANGUAGES C)
set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")
include(CTest)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -g)
cmake_minimum_required()
INCLUDE( FindPkgConfig )
# find_package(PkgConfig REQUIRED)
pkg_check_modules(PNG REQUIRED libpng)
set(LIBS ${PROJECT_SOURCE_DIR}/libs)

include_directories(${PNG_INCLUDE_DIRS} )
link_directories (${PNG_LIBRARY_DIRS})

enable_testing()


if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


add_subdirectory(libs/logger )
add_subdirectory(libs/paint-piet-runtime)
add_subdirectory(tests)
add_subdirectory(src)
# set(CMAKE_CTEST_ARGUMENTS --output-on-falure)



