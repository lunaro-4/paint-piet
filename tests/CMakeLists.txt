# if(COMMAND cmake_policy)
# 	cmake_policy(SET CMP0003 NEW)
# endif(COMMAND cmake_policy)

# pkg_check_modules(Check REQUIRED check)
find_package(check)

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

include_directories(${check_INCLUDE_DIRS})
link_directories (${check_LIBRARY_DIRS})


set(SOURCE test.c test_suits_and_cases.c)
set(TESTS_OUT tests)
if (DEFINED ENV{OS})
	set(SOURCE ${SOURCE} ../src/realpath.c)
	# set(TESTS_OUT tests.exe)
endif()

add_executable(${TESTS_OUT} ${SOURCE})
target_link_libraries(${TESTS_OUT} ${check_LIBRARIES} ${PNG_LIBRARIES} paint-piet-runtime logger )
target_include_directories(${TESTS_OUT} PUBLIC ${PROJECT_SOURCE_DIR}/src ${LIBS}/logger/include ${LIBS}/paint-piet-runtime/include )

# add_test(NAME check_test COMMAND test WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
add_test(NAME test_params COMMAND ${PROJECT_SOURCE_DIR}/out/${TESTS_OUT} params )
add_test(NAME test_colors COMMAND ${PROJECT_SOURCE_DIR}/out/${TESTS_OUT} colors )
add_test(NAME test_compare COMMAND ${PROJECT_SOURCE_DIR}/out/${TESTS_OUT} compare )
add_test(NAME test_codels COMMAND ${PROJECT_SOURCE_DIR}/out/${TESTS_OUT} codels )
set_tests_properties(test_params test_colors test_compare test_codels PROPERTIES TIMEOUT 30) 


# include(FindValgrind)
# add_custom_target(valgrind_test_sample
#   COMMAND ${VALGRIND_PROGRAM} --leak-check=full $<TARGET_FILE:tests>
#   DEPENDS tests
# )
