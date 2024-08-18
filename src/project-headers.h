#ifndef HEADRERS
#define HEADRERS
#include <stdbool.h>
#include <dirent.h>
#include "paint-piet-runtime.h"
// #include "custom_utils.h"

#endif // !HEADRERS

#ifndef CUSTOM_UTILS
#define CUSTOM_UTILS


void print_2d_int(int height, int width, int arr[height][width]);


void print_int_array(int arr[], int arr_len);

#ifdef _WIN32

char *realpath(const char *path, char resolved_path[PATH_MAX]);
#endif // _WIN32

#endif // !CUSTOM_UTILS
