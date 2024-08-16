#include "paint-piet-runtime.h"

#ifndef PIET_COMMANDS
#define PIET_COMMANDS
int choose_light_actions (int hue_steps);
int choose_normal_actions (int hue_steps);
int choose_dark_actions (int hue_steps);

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

#endif // !PIET_COMMANDS
