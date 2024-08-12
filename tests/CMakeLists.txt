
# pkg_check_modules(Check REQUIRED check)
find_package(Check)

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

include_directories(${Check_INCLUDE_DIRS})
link_directories (${Check_LIBRARY_DIRS})


add_executable(tests test.c ../src/colormatrix.c ../src/custom_utils.c ../logger/logger.c test_suits_and_cases.c)
target_link_libraries(tests ${CHECK_LIBRARIES} )
include_directories(${PROJECT_SOURCE_DIR})
target_link_libraries (tests ${PNG_LIBRARIES})

# add_test(NAME check_test COMMAND test WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
add_test(NAME test_params COMMAND ${PROJECT_SOURCE_DIR}/out/tests params )
add_test(NAME test_colors COMMAND ${PROJECT_SOURCE_DIR}/out/tests colors )
add_test(NAME test_compare COMMAND ${PROJECT_SOURCE_DIR}/out/tests compare )
set_tests_properties(test_params test_colors test_compare PROPERTIES TIMEOUT 30) 


include(FindValgrind)
add_custom_target(valgrind_test_sample
  COMMAND ${VALGRIND_PROGRAM} --leak-check=full $<TARGET_FILE:tests>
  DEPENDS tests
)
