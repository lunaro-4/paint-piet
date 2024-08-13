#ifndef HEADRERS
#define HEADRERS
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <dirent.h>
#include <stdbool.h>
// #include "custom_utils.h"

#endif // !HEADRERS


#ifndef COLORMATRIX
#define COLORMATRIX
void create_matrix(FILE *fptr,  int width, int height, struct color *matrix[height][width]);

void get_rows(FILE *fptr, png_bytepp *rows);

void get_height_and_width(FILE *fptr, int* height, int* width);

void test_nerby(int y, int x, int height, int width, int codel_index, int map[][width], struct color *matrix[][width], int *codel_size);

void fill_2d_map(int height, int width, int map[][width], struct color *matrix[][width], int *n_of_codels, struct codel *codel_array[]);

void find_neighbor_codels(int height, int width, int map[][width], struct codel *codel_array[]);

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

#endif // !CUSTOM_UTILS

