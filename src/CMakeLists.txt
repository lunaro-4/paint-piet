# set(LOCAL_LIBS main.c colormatrix.c custom_utils.c runtime.c piet-commands.c)
add_executable(main main.c local_prints.c )
target_link_libraries (main  paint-piet-runtime.so)
target_include_directories(main PRIVATE ${LIBS}/paint-piet-runtime/include)


# set(CMAKE_SYSTEM_NAME Windows)
# set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)
#
# # cross compilers to use for C, C++ and Fortran
# set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
# set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
# set(CMAKE_Fortran_COMPILER ${TOOLCHAIN_PREFIX}-gfortran)
# set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)
#
# # target environment on the build host system
# set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})
#
# # modify default behavior of FIND_XXX() commands
# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# add_executable(main.exe ${LOCAL_LIBS})
# target_link_libraries (main.exe ${PNG_LIBRARIES})
