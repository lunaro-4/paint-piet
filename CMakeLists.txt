# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
cmake_minimum_required(VERSION 3.23)
project(paint-piet LANGUAGES C)
set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")
include(CTest)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
INCLUDE( FindPkgConfig )
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(PNG REQUIRED libpng)
set(LIBS ${PROJECT_SOURCE_DIR}/libs)

include_directories(${LIBS}/logger/include)

enable_testing()


if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


set(BUILD_TYPE "0$ENV{BUILD_TYPE}")

set(LIB_KEYWORD SHARED)
if ((${BUILD_TYPE} STREQUAL "0mono") OR (${BUILD_TYPE} STREQUAL "0MONO"))
	set(LIB_KEYWORD "")
endif()


add_subdirectory(libs/logger )
add_subdirectory(libs/paint-piet-runtime)
add_subdirectory(tests)
add_subdirectory(src)
add_subdirectory(src/gui)
# set(CMAKE_CTEST_ARGUMENTS --output-on-falure)



