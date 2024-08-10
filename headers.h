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

#define WHITE_INDEX 1
#define BLACK_INDEX 0
#define CODEL_ARRAY_SIZE 500

#ifndef FUNCS_1_INCLUDED
#define FUNCS_1_INCLUDED
void create_matrix(png_bytepp png_rows,  int width, int height, struct color *matrix[height][width]);

void get_rows(FILE *fptr, png_bytepp *rows);

void get_height_and_width(FILE *fptr, int* height, int* width);

void test_nerby(int y, int x, int height, int width, int codel_index, int map[][width], struct color *matrix[][width]);

void fill_2d_map(int height, int width, int map[][width], struct color *matrix[][width], int *n_of_codels, struct color *codel_array[]);

#endif // !FUNCS_1_INCLUDED

#ifndef FUNCS_2_INCLUDED
#define FUNCS_2_INCLUDED

int get_chunk_value(FILE * fptr);

void print_color_matrix(int height, int widht, struct color *matrix[height][widht]);

void print_2d_int(int height, int width, int arr[height][width]);

void free_2d_colors(int height, int width, struct color *arr[][width]);

bool is_same_color(struct color *a, struct color *b);

bool is_black(struct color *col);

bool is_white(struct color *col);

#endif // !FUNCS_2_INCLUDED

