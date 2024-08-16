// #include "headers.h"
#include "../include/paint-piet-runtime.h"
#include <stdio.h>



int choose_light_actions (int hue_steps)
{
	switch (hue_steps) {
		case 0:
			perror("Incorrect action! Same color!");
			return 0;
		case 1:
			return PIET_ADD;
		case 2:
			return PIET_DIVIDE;
		case 3:
			return PIET_GREATER;
		case 4:
			return PIET_DUPLICATE;
		case 5:
			return PIET_INPUT_CHAR;
		default:
			perror("Unknown action");
			return 0;
	}
}
int choose_normal_actions (int hue_steps)
{
	switch (hue_steps) {
		case 0:
			return PIET_PUSH;
		case 1:
			return PIET_SUBSTRACT;
		case 2:
			return PIET_MODULO;
		case 3:
			return PIET_POINTER;
		case 4:
			return PIET_ROLL;
		case 5:
			return PIET_OUTPUT_NUM;
		default:
			perror("Unknown action");
			return 0;
	}

}

int choose_dark_actions (int hue_steps)
{
	switch (hue_steps) {
		case 0:
			return PIET_POP;
		case 1:
			return PIET_MULTIPLY;
		case 2:
			return PIET_NOT;
		case 3:
			return PIET_SWITCH;
		case 4:
			return PIET_INPUT_NUM;
		case 5:
			return PIET_OUTPUT_CHAR;
		default:
			perror("Unknown action");
			return 0;
	}
}
void rotate_pointer(struct pointer *pointer, int rotation_times)
{
	bool clockwise = rotation_times > 0;
	enum direction *dp = &pointer->DP;

	if (clockwise)
	{
		for (int i = 0; i < rotation_times; i++)
		{
			switch (*dp) {
				case DP_RIGHT:
					*dp = DP_DOWN;
					break;
				case DP_DOWN:
					*dp = DP_LEFT;
					break;
				case DP_LEFT:
					*dp = DP_UP;
					break;
				case DP_UP:
					*dp = DP_RIGHT;
					break;
			}
		}
	}
	else
	{
		rotation_times *= -1;
		for (int i = 0; i < rotation_times; i++)
			switch (*dp) {
				case DP_RIGHT:
					*dp = DP_UP;
					break;
				case DP_DOWN:
					*dp = DP_RIGHT;
					break;
				case DP_LEFT:
					*dp = DP_DOWN;
					break;
				case DP_UP:
					*dp = DP_LEFT;
					break;
			}
	}
}

void switch_pointer (struct pointer *pointer, int switch_times)
{
	enum moves *cc = &pointer->CC;
	for (int i = 0; i < switch_times; i++)
		switch (*cc) {
			case CC_LEFT:
				*cc = CC_RIGHT;
				break;
			case CC_RIGHT:
				*cc = CC_LEFT;
				break;
		}
}

int piet_push(int stack[], int **stack_ptr, int push_value)
{
	if (*stack_ptr - stack +1 > STACK_MAX_SIZE)
	{
		perror("PUSH: Stack boundry reached!");
		return 1;
	}
	**stack_ptr = push_value;
	(*stack_ptr)++;
	return 0;
}

int piet_pop(int stack[], int **stack_ptr)
{
	if (*stack_ptr - stack <= 0)
	{
		perror("POP: Stack boundry reached!");
		return 1;
	}
	**stack_ptr = 0;
	(*stack_ptr)--;
	return 0;
}

int piet_add(int stack[], int **stack_ptr)
{
	int *local_ptr = (*stack_ptr) - 1;
	int value_1 = *(local_ptr), value_2 = *(local_ptr - 1);
	int result = value_2 + value_1;
	piet_pop(stack, stack_ptr);
	piet_pop(stack, stack_ptr);
	piet_push(stack, stack_ptr, result);
	return 0;

}

int piet_substract (int stack[], int **stack_ptr)
{
	// note the order
	int *local_ptr = (*stack_ptr) - 1;
	int value_1 = *(local_ptr), value_2 = *(local_ptr - 1);
	int result = value_2 - value_1;
	piet_pop(stack, stack_ptr);
	piet_pop(stack, stack_ptr);
	piet_push(stack, stack_ptr, result);
	return 0;
}
int piet_multiply (int stack[], int **stack_ptr)
{
	int *local_ptr = (*stack_ptr) - 1;
	int value_1 = *(local_ptr), value_2 = *(local_ptr - 1);
	int result = value_1 * value_2;
	piet_pop(stack, stack_ptr);
	piet_pop(stack, stack_ptr);
	piet_push(stack, stack_ptr, result);
	return 0;
}
int piet_divide (int stack[], int **stack_ptr)
{
	// note the order
	int *local_ptr = (*stack_ptr) - 1;
	int value_1 = *(local_ptr), value_2 = *(local_ptr - 1);
	int result = value_2 / value_1;
	piet_pop(stack, stack_ptr);
	piet_pop(stack, stack_ptr);
	piet_push(stack, stack_ptr, result);
	return 0;
}
int piet_modulo (int stack[], int **stack_ptr)
{
	// note the order
	int *local_ptr = (*stack_ptr) - 1;
	int value_1 = *(local_ptr), value_2 = *(local_ptr - 1);
	int result = value_2 % value_1;
	piet_pop(stack, stack_ptr);
	piet_pop(stack, stack_ptr);
	piet_push(stack, stack_ptr, result);
	return 0;
}

int piet_not (int stack[], int **stack_ptr)
{
	**stack_ptr = **stack_ptr == 0;
	return 0;
}

int piet_greater (int stack[], int **stack_ptr)
{
	// note the order
	int *local_ptr = (*stack_ptr) - 1;
	int value_1 = *(local_ptr), value_2 = *(local_ptr - 1);
	int result = value_2 > value_1;
	piet_pop(stack, stack_ptr);
	piet_pop(stack, stack_ptr);
	piet_push(stack, stack_ptr, result);
	return 0;
}

int piet_pointer (int stack[], int **stack_ptr, struct pointer *pointer)
{
	int value = *(*stack_ptr - 1);
	rotate_pointer(pointer, value);
	piet_pop(stack, stack_ptr);
	return 0;
}

int piet_switch (int stack[], int **stack_ptr, struct pointer *pointer)
{
	int value = **stack_ptr;
	if (value < 0) value *= -1;
	switch_pointer(pointer, value);
	piet_pop(stack, stack_ptr);
	return 0;
}

int piet_duplicate (int stack[], int **stack_ptr)
{
	int value = *(*(stack_ptr) -1);
	piet_push(stack, stack_ptr, value);
	return 0;
}
int piet_roll (int stack[], int **stack_ptr)
{
	int temp_stack[STACK_MAX_SIZE], temp_temp_stack[STACK_MAX_SIZE+1];
	
	int *local_ptr = (*stack_ptr) - 1;
	int value_1 = *(local_ptr), value_2 = *(local_ptr - 1);
	int rolls = value_1 + 0, depth = value_2 + 0;
	if (*stack_ptr - stack < rolls)
	{
		perror("Requested n of rolls is greater then current stack size");
		return 1;
	}
	piet_pop(stack, stack_ptr);
	piet_pop(stack, stack_ptr);

	for (int i = 0; i < depth; i++)
	{
		temp_stack[i] = *(*(stack_ptr) - i);
		piet_pop(stack, stack_ptr);
	}

	for (int i = 0; i < rolls; i++)
	{
		for (int j = 0; j < depth - 1; j++)
			temp_temp_stack[j + 1] = temp_stack[j];
		temp_temp_stack[0] = temp_stack[depth - 1];
		for (int j = 0; j < depth; j++)
			temp_stack[j] = temp_stack[j];
	}
	// for (int i = depth - 1; i >= 0; i--)
	// 	piet_push(stack, stack_ptr, temp_stack[i]);
	for (int i = 0; i < depth; i++)
		piet_push(stack, stack_ptr, temp_stack[i]);

	return 0;
}
int piet_input_num (int stack[], int **stack_ptr)
{
	int input;
	printf("Enter a number: ");
	int result = scanf("%i", &input);
	// putchar('\n');
	if (result != 1) 
	{
		perror("Error reading number");
		return 1;
	}
	piet_push(stack, stack_ptr, input);
	return 0;
}
int piet_input_char (int stack[], int **stack_ptr)
{
	char input;
	printf("Enter a character: ");
	int result = scanf("%c", &input);
	// putchar('\n');
	if (result != 1) 
	{
		perror("Error reading character");
		return 1;
	}
	piet_push(stack, stack_ptr, input);
	return 0;
}


int piet_output_char (int stack[], int **stack_ptr)
{
	putchar(*(*stack_ptr -1));
	piet_pop(stack, stack_ptr);
	return 0;
}
int piet_output_num (int stack[], int **stack_ptr)
{
	printf("%i", *(*stack_ptr -1));
	piet_pop(stack, stack_ptr);
	return 0;
}

void _piet_debug (int hue_steps, int light_steps)
{
	printf("Input: hue_steps = %i, light_steps = %i\n", hue_steps, light_steps);
	switch (light_steps) {
		case 0:
			switch (hue_steps) {
				case 0:
					return;
				case 1:
					printf("Command: %s\n", "ADD");
					break;
				case 2:
					printf("Command: %s\n", "DIVIDE");
					break;
				case 3:
					printf("Command: %s\n", "GREATER");
					break;
				case 4:
					printf("Command: %s\n", "DUPLICATE");
					break;
				case 5:
					printf("Command: %s\n", "PIET_INPUT_CHAR");
					break;
			}
			break;
		case 1:
			switch (hue_steps) {
				case 0:
					printf("Command: %s\n", "PUSH");
					break;
				case 1:
					printf("Command: %s\n", "PIET_SUBSTRACT");
					break;
				case 2:
					printf("Command: %s\n", "MODULO");
					break;
				case 3:
					printf("Command: %s\n", "PIET_POINTER");
					break;
				case 4:
					printf("Command: %s\n", "PIET_ROLL");
					break;
				case 5:
					printf("Command: %s\n", "PIET_OUTPUT_NUM");
					break;
			}
			break;
		case 2:
			switch (hue_steps) {
				case 0:
					printf("Command: %s\n", "POP");
					break;
				case 1:
					printf("Command: %s\n", "PIET_MULTIPLY");
					break;
				case 2:
					printf("Command: %s\n", "PIET_NOT");
					break;
				case 3:
					printf("Command: %s\n", "SWITCH");
					break;
				case 4:
					printf("Command: %s\n", "PIET_INPUT_NUM");
					break;
				case 5:
					printf("Command: %s\n", "PIET_OUTPUT_CHAR");
					break;
			}
	}
}
int process_piet (enum piet_action command, struct pointer *pointer, int codel_value, int stack[], int **stack_ptr)
{
	switch (command) {
		case PIET_PUSH:
			return piet_push(stack, stack_ptr, codel_value);
		case PIET_POP:
			return piet_pop(stack, stack_ptr);
		case PIET_ADD:
			return piet_add(stack, stack_ptr);
		case PIET_SUBSTRACT:
			return piet_substract(stack, stack_ptr);
		case PIET_MULTIPLY:
			return piet_multiply(stack, stack_ptr);
		case PIET_DIVIDE:
			return piet_divide(stack, stack_ptr);
		case PIET_MODULO:
			return piet_modulo(stack, stack_ptr);
		case PIET_NOT:
			return piet_not(stack, stack_ptr);
		case PIET_GREATER:
			return piet_greater(stack, stack_ptr);
		case PIET_POINTER:
			return piet_pointer(stack, stack_ptr, pointer);
		case PIET_SWITCH:
			return piet_switch(stack, stack_ptr, pointer);
		case PIET_DUPLICATE:
			return piet_duplicate(stack, stack_ptr);
		case PIET_ROLL:
			return piet_roll(stack, stack_ptr);
		case PIET_INPUT_NUM:
			return piet_input_num(stack, stack_ptr);
		case PIET_INPUT_CHAR:
			return piet_input_char(stack, stack_ptr);
		case PIET_OUTPUT_NUM:
			return piet_output_num(stack, stack_ptr);
		case PIET_OUTPUT_CHAR:
			return piet_input_num(stack, stack_ptr);

	}

	return 0;
}
void process_move (int hue_steps, int light_steps, int codel_value, struct pointer *pointer, int stack[], int **stack_ptr)
{
	// int hue_steps, light_steps;
	//
	// struct codel from = *codel_array[pointer->codels[0]], to = *codel_array[pointer->codels[1]];
	// count_steps(&from.color, &to.color, &hue_steps, &light_steps);

	int	res = 0;
	
	enum piet_action command;

	switch (light_steps) {
		case 0:
			switch (hue_steps) {
				case 0:
					return;
				case 1:
					res = piet_add(stack, stack_ptr);
					break;
				case 2:
					res = piet_divide(stack, stack_ptr);
					break;
				case 3:
					res = piet_greater(stack, stack_ptr);
					break;
				case 4:
					res = piet_duplicate(stack, stack_ptr);
					break;
				case 5:
					res = piet_input_char(stack, stack_ptr);
			}
			break;
		case 1:
			switch (hue_steps) {
				case 0:
					res = piet_push(stack, stack_ptr, codel_value);
					break;
				case 1:
					res = piet_substract(stack, stack_ptr);
					break;
				case 2:
					res = piet_modulo(stack, stack_ptr);
					break;
				case 3:
					res = piet_pointer(stack, stack_ptr, pointer);
					break;
				case 4:
					res = piet_roll(stack, stack_ptr);
					break;
				case 5:
					res = piet_output_num(stack , stack_ptr);
					break;
			}
			break;
		case 2:
			switch (hue_steps) {
				case 0:
					res = piet_pop(stack, stack_ptr);
					break;
				case 1:
					res = piet_multiply(stack, stack_ptr);
					break;
				case 2:
					res = piet_not(stack, stack_ptr);
					break;
				case 3:
					res = piet_switch(stack, stack_ptr, pointer);
					break;
				case 4:
					res = piet_input_num(stack, stack_ptr);
					break;
				case 5:
					res = piet_output_char(stack, stack_ptr);
					break;
			}
	}





}
