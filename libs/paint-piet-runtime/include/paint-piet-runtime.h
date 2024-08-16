#include <stdbool.h>
#include <stdio.h>
#include <png.h>

#ifndef PAINT_PIET_LIBRARY
#define PAINT_PIET_LIBRARY

#define STACK_MAX_SIZE 200
#define WHITE_INDEX 1
#define BLACK_INDEX 0

enum piet_hue {
	PIET_RED = 0, PIET_YELLOW = 1 , PIET_GREEN = 2 , PIET_CYAN = 3, PIET_BLUE = 4, PIET_MAGENTA = 5
};

enum piet_light {
	PIET_LIGHT = 0, PIET_NORMAL, PIET_DARK
};

enum piet_action {
	PIET_PUSH, PIET_POP,
	PIET_ADD, PIET_SUBSTRACT, PIET_MULTIPLY,
	PIET_DIVIDE, PIET_MODULO, PIET_NOT,
	PIET_GREATER, PIET_POINTER, PIET_SWITCH,
	PIET_DUPLICATE, PIET_ROLL, PIET_INPUT_NUM,
	PIET_INPUT_CHAR, PIET_OUTPUT_NUM, PIET_OUTPUT_CHAR
};

enum moves {
	CC_LEFT = 1, CC_RIGHT = 2
};

enum direction {
	 DP_RIGHT = 0, DP_DOWN = 1, DP_LEFT = 2, DP_UP = 3
};

struct color {
	int red;
	int green;
	int blue;
};

struct codel {
	int size;
	struct color color;
	int corner_points[4][3];	
};

struct pointer {
	int codels[2]; // old & new
	enum direction DP;
	enum moves CC;
	bool cc_switched;
};

void count_steps (struct color *a, struct color *b, int *hue_steps, int *light_steps);

int process_piet (enum piet_action command, struct pointer *pointer, int codel_value, int stack[], int **stack_ptr);

// void process_move (struct codel *codel_array[], struct pointer *pointer, int stack[], int **stack_ptr);

void process_move (int hue_steps, int light_steps, int codel_value, struct pointer *pointer, int stack[], int **stack_ptr);

void _piet_debug (int hue_steps, int light_steps);

#endif // !PAINT_PIET_LIBRARY

#ifndef COLORMATRIX
#define COLORMATRIX
int create_matrix(FILE *fptr,  int width, int height, struct color *matrix[height][width]);

void get_rows(FILE *fptr, png_bytepp *rows);

void get_height_and_width(FILE *fptr, int* height, int* width);

void test_nerby(int y, int x, int height, int width, int codel_index, int map[][width], struct color *matrix[][width], int *codel_size);

void fill_2d_map(int height, int width, int map[][width], struct color *matrix[][width], int *n_of_codels, struct codel *codel_array[]);

void find_codels_corner_points(int height, int width, int map[][width], struct codel *codel_array[]);

#endif // !COLORMATRIX

#ifndef PAINT_PIET_UTILS
#define PAINT_PIET_UTILS

int get_chunk_value(FILE * fptr);

void print_color_matrix(int height, int widht, struct color *matrix[height][widht]);

bool is_light_hue(int color);

bool is_same_color(struct color *a, struct color *b);

bool is_same_color_fuzz(struct color *a, struct color *b);

bool is_black(struct color *col);

bool is_white(struct color *col);

bool process_pointer(int *y, int *x, int height, int width, int map[][width], struct pointer *pointer, struct codel *codel_array[], int *bumps);

void free_2d_colors(int height, int width, struct color *arr[][width]);

void print_codel_array_colors(struct codel *codel_array[], int n_of_codels);

void print_codel_array_corner_points(struct codel *codel_array[], int n_of_codels);

#endif // !PAINT_PIET_UTILS
