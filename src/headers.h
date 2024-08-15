#ifndef HEADRERS
#define HEADRERS
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <dirent.h>
#include "paint-piet.h"
// #include "custom_utils.h"

#endif // !HEADRERS


#ifndef COLORMATRIX
#define COLORMATRIX
int create_matrix(FILE *fptr,  int width, int height, struct color *matrix[height][width]);

void get_rows(FILE *fptr, png_bytepp *rows);

void get_height_and_width(FILE *fptr, int* height, int* width);

void test_nerby(int y, int x, int height, int width, int codel_index, int map[][width], struct color *matrix[][width], int *codel_size);

void fill_2d_map(int height, int width, int map[][width], struct color *matrix[][width], int *n_of_codels, struct codel *codel_array[]);

void find_codels_corner_points(int height, int width, int map[][width], struct codel *codel_array[]);

#endif // !COLORMATRIX

#ifndef CUSTOM_UTILS
#define CUSTOM_UTILS

int get_chunk_value(FILE * fptr);

void print_color_matrix(int height, int widht, struct color *matrix[height][widht]);

void print_2d_int(int height, int width, int arr[height][width]);

void free_2d_colors(int height, int width, struct color *arr[][width]);

bool is_same_color(struct color *a, struct color *b);

bool is_black(struct color *col);

bool is_white(struct color *col);

void print_codel_array_colors(struct codel *codel_array[], int n_of_codels);

void print_codel_array_corner_points(struct codel *codel_array[], int n_of_codels);
#endif // !CUSTOM_UTILS

#ifndef RUNTIME
#define RUNTIME

void process_pointer(int *y, int *x, int height, int width, int map[][width], struct pointer *pointer, struct codel *codel_array[], int *bumps);

#endif // !RUNTIME

#ifndef PIET_COMMANDS
#define PIET_COMMANDS

int choose_light_actions (int hue_steps);
int choose_normal_actions (int hue_steps);
int choose_dark_actions (int hue_steps);

#endif // !PIET_COMMANDS


