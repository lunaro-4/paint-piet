
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


add_executable(tests test.c ../colormatrix.c ../custom_utils.c)
target_link_libraries(tests ${CHECK_LIBRARIES} )
# target_include_directories(tests PRIVATE "../")
include_directories(${PROJECT_SOURCE_DIR})
target_link_libraries (tests ${PNG_LIBRARIES})

# Create testing target and redirect its output to `Testing` folder
# add_test(NAME check_test COMMAND test WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
add_test(NAME check_test COMMAND ${PROJECT_SOURCE_DIR}/out/tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS tests)
set_tests_properties(check_test PROPERTIES TIMEOUT 30) 

# Aditional Valgrind test to check memory leaks in code
include(FindValgrind)

add_custom_target(valgrind_test_sample
  COMMAND ${VALGRIND_PROGRAM} --leak-check=full $<TARGET_FILE:tests>
  DEPENDS tests
)
