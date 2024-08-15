#include <stdbool.h>

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
#ifndef PIET_COMMANDS
#define PIET_COMMANDS
int choose_light_actions (int hue_steps);
int choose_normal_actions (int hue_steps);
int choose_dark_actions (int hue_steps);
/*
void rotate_pointer(struct pointer *pointer, int rotation_times);
void switch_pointer (struct pointer *pointer, int switch_times);
int piet_push(int stack[], int **stack_ptr, int push_value);
int piet_pop(int stack[], int **stack_ptr);
int piet_add(int stack[], int **stack_ptr);
int piet_substract (int stack[], int **stack_ptr);
int piet_multiply (int stack[], int **stack_ptr);
int piet_divide (int stack[], int **stack_ptr);
int piet_modulo (int stack[], int **stack_ptr);
int piet_not (int stack[], int **stack_ptr);
int piet_greater (int stack[], int **stack_ptr);
int piet_pointer (int stack[], int **stack_ptr, struct pointer *pointer);
int piet_switch (int stack[], int **stack_ptr, struct pointer *pointer);
int piet_duplicate (int stack[], int **stack_ptr);
int piet_roll (int stack[], int **stack_ptr);
int piet_input_num (int stack[], int **stack_ptr);
int piet_input_char (int stack[], int **stack_ptr);
int piet_output_char (int stack[], int **stack_ptr);
int piet_output_num (int stack[], int **stack_ptr);
*/
#endif // !PIET_COMMANDS
