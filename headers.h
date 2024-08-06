#ifndef HEADRERS
#define HEADRERS
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
// #include "custom_utils.h"

#endif // !HEADRERS

#ifndef FUNCS_1_INCLUDED
#define FUNCS_1_INCLUDED
void create_matrix(png_bytepp png_rows,  int width, int height, struct color *matrix[height][width]);

void get_rows(FILE *fptr, png_bytepp *rows);

void get_width_and_height(FILE *fptr, int* width, int* height);


#endif // !FUNCS_1_INCLUDED

#ifndef FUNCS_2_INCLUDED
#define FUNCS_2_INCLUDED

int get_chunk_value(FILE * fptr);

void print_color_matrix(int height, int widht, struct color *matrix[height][widht]);

#endif // !FUNCS_2_INCLUDED

