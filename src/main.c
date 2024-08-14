#include "headers.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define STACK_MAX_SIZE 200
#define MAX_COLOR 0xff
#define MID_COLOR 0x00

void rotate_pointer(struct pointer *pointer, int rotation_times)
{
	bool clockwise = rotation_times > 0;
	enum direction *dp = &pointer->DP;

	if (clockwise)
		for (int i = 0; i < rotation_times; i++)
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
	else
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
	(*stack_ptr)++;
	**stack_ptr = push_value;
	return 0;
}

int piet_pop(int stack[], int **stack_ptr)
{
	**stack_ptr = 0;
	(*stack_ptr)--;
	return 0;
}

int piet_add(int stack[], int **stack_ptr)
{
	int value_1 = **(stack_ptr), value_2 = *(*(stack_ptr) - 1);
	piet_pop(stack, stack_ptr);
	**stack_ptr = value_1 + value_2;
	return 0;

}

int piet_substract (int stack[], int **stack_ptr)
{
	// note the order
	int value_1 = **(stack_ptr), value_2 = *(*(stack_ptr) - 1);
	piet_pop(stack, stack_ptr);
	**stack_ptr = value_2 - value_1;
	return 0;
}
int piet_multiply (int stack[], int **stack_ptr)
{
	int value_1 = **(stack_ptr), value_2 = *(*(stack_ptr) - 1);
	piet_pop(stack, stack_ptr);
	**stack_ptr = value_1 * value_2;
	return 0;
}
int piet_divide (int stack[], int **stack_ptr)
{
	// note the order
	int value_1 = **(stack_ptr), value_2 = *(*(stack_ptr) - 1);
	piet_pop(stack, stack_ptr);
	**stack_ptr = value_2 / value_1;
	return 0;
}
int piet_modulo (int stack[], int **stack_ptr)
{
	// note the order
	int value_1 = **(stack_ptr), value_2 = *(*(stack_ptr) - 1);
	piet_pop(stack, stack_ptr);
	**stack_ptr = value_2 % value_1;
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
	int value_1 = **(stack_ptr), value_2 = *(*(stack_ptr) - 1);
	piet_pop(stack, stack_ptr);
	**stack_ptr = value_2 > value_1;
	return 0;
}

int piet_pointer (int stack[], int **stack_ptr, struct pointer *pointer)
{
	int value = **stack_ptr;
	piet_pop(stack, stack_ptr);
	rotate_pointer(pointer, value);
	return 0;
}

int piet_switch (int stack[], int **stack_ptr, struct pointer *pointer)
{
	int value = **stack_ptr;
	piet_pop(stack, stack_ptr);
	if (value < 0) value *= -1;
	switch_pointer(pointer, value);
	return 0;
}

int piet_duplicate (int stack[], int **stack_ptr)
{
	piet_push(stack, stack_ptr, **stack_ptr);
	return 0;
}
int piet_roll (int stack[], int **stack_ptr)
{
	int temp_stack[STACK_MAX_SIZE], temp_temp_stack[STACK_MAX_SIZE+1];
	
	int rolls = **stack_ptr, depth = *(*(stack_ptr) - 1);
	if (stack - *stack_ptr < rolls)
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
			temp_temp_stack[j+1] = temp_stack[j];
		temp_temp_stack[0] = temp_stack[depth - 1];
		for (int j = 0; j < depth; j++)
			temp_stack[j] = temp_stack[j];
	}
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
	putchar(**stack_ptr);
	piet_pop(stack, stack_ptr);
	return 0;
}
int piet_output_num (int stack[], int **stack_ptr)
{
	printf("%i", **stack_ptr);
	piet_pop(stack, stack_ptr);
	return 0;
}

int process_piet (enum piet_action command, struct pointer *pointer, int codel_value, int stack[], int **stack_ptr)
{
	switch (command) {
		case PUSH:
			return piet_push(stack, stack_ptr, codel_value);
		case POP:
			return piet_pop(stack, stack_ptr);
		case ADD:
			return piet_add(stack, stack_ptr);
		case SUBSTRACT:
			return piet_substract(stack, stack_ptr);
		case MULTIPLY:
			return piet_multiply(stack, stack_ptr);
		case DIVIDE:
			return piet_divide(stack, stack_ptr);
		case MODULO:
			return piet_modulo(stack, stack_ptr);
		case NOT:
			return piet_not(stack, stack_ptr);
		case GREATER:
			return piet_greater(stack, stack_ptr);
		case POINTER:
			return piet_pointer(stack, stack_ptr, pointer);
		case SWITCH:
			return piet_switch(stack, stack_ptr, pointer);
		case DUPLICATE:
			return piet_duplicate(stack, stack_ptr);
		case ROLL:
			return piet_roll(stack, stack_ptr);
		case INPUT_NUM:
			return piet_input_num(stack, stack_ptr);
		case INPUT_CHAR:
			return piet_input_char(stack, stack_ptr);
		case OUTPUT_NUM:
			return piet_output_num(stack, stack_ptr);
		case OUTPUT_CHAR:
			return piet_input_num(stack, stack_ptr);

	}

	return 0;
}



int get_color_light (struct color *color)
{
	if (color->red > 0 && color->green > 0 && color->blue > 0)
		return LIGHT;
	else
	if (color->red < 0xff && color->green < 0xff && color->blue < 0xff)
		return DARK;
	else
		return NORMAL;
}

int get_color_hue (struct color *color, enum piet_light light)
{
	bool red = false, green = false, blue = false;
	/* TODO:
	 *	LIGHT == MAX_COLOR
	 *	NORMAL > MID_COLOR
	 *	DARK <= MID_COLOR
	 *	*/
	switch (light) {
		case LIGHT:
			;
		case NORMAL:
			if (color->red == MAX_COLOR)
				red = true;
			if (color->green == MAX_COLOR)
				green = true;
			if (color->blue == MAX_COLOR)
				blue = true;
			break;
		case DARK:
			if (color->red >= MID_COLOR)
				red = true;
			if (color->green >= MID_COLOR)
				green = true;
			if (color->blue >= MID_COLOR)
				blue = true;

	}
	// int result = 0;

	/* if (red)
		result += RED;
	if (green)
		result += GREEN;
	if (blue)
		result += BLUE; */

	if (red && green)
		return YELLOW;
	if (green && blue)
		return CYAN;
	if (blue && red)
		return MAGENTA;
	if (red)
		return RED;
	if (green)
		return GREEN;
	if (blue)
		return BLUE;

	perror("No hue match found!");
	return NULL;

}

void count_steps (struct color *a, struct color *b, int *hue_steps, int *light_steps)
{
	*hue_steps = *light_steps = 0;

	enum piet_hue a_hue = 0, b_hue = 0;
	enum piet_light a_light = 0, b_light = 0;

	a_light = get_color_light(a);
	b_light = get_color_light(b);

	a_hue = get_color_hue(a, a_light);
	b_hue = get_color_hue(b, b_light);

	int local_hue_steps = b_hue - a_hue,
		local_light_steps = b_light - a_light;

	if (local_light_steps < 0)
		local_light_steps += 2;

	*light_steps = local_light_steps;

	if (local_hue_steps < 0)
		local_hue_steps += 5;

	*hue_steps = local_hue_steps;



	/* int r_diff = a->red - b->red, g_diff = a->green - b->green, b_diff = a->blue - a->blue;

	if ((r_diff >= 0 && g_diff >= 0) || (g_diff >= 0 && b_diff >= 0) || (b_diff >= 0 && r_diff >= 0))
	{
		++*hue_steps;
	} */

}



void process_move (struct codel *from, struct codel *to, int stack[])
{
	int hue_steps, light_steps;
	count_steps(&from->color, &to->color, &hue_steps, &light_steps);


	switch (hue_steps) {
		case 0:
			
	}



}





int main(int argc, char *argv[])
{
	struct codel cod;

	char* file_path;

	if (argc > 1) {
		file_path = argv[1];
	}
	else {
		file_path = "in.png";
	}
	FILE *fptr = fopen(file_path, "r");

	if (fptr == NULL) {
		perror("error openining file");
		return 1;
	}

	int height, width;
	get_height_and_width(fptr, &height, &width);

	fclose(fptr);
	fptr = fopen(file_path, "r");


	struct color *matrix[height][width];

	for (int i = 0; i < height; i++) {
        for (int j = 0; j < width  ; j++ ) {
			static struct color *c;
			c = malloc(sizeof(struct color));
			matrix[i][j] = c;
		}
	}

	int res = create_matrix(fptr, width, height, matrix);
	if (res) return 1;


	int map[height][width], n_of_codels;
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			map[y][x] = -1;

	struct codel *codel_array[CODEL_ARRAY_SIZE];
	fill_2d_map(height, width, map, matrix, &n_of_codels, codel_array);
	
	find_codels_corner_points(height, width, map, codel_array);

	struct pointer pointer = {{0, 2}, DP_RIGHT, CC_LEFT, false};


	int current_y = 0, current_x = 0, bumps = 0;

	// for (int i = 0; i < 50; i++)
	while (bumps < 8) // DP should see all 4 directions
	{
		process_pointer(&current_y, &current_x, height, width, map, &pointer, codel_array, &bumps);
		// printf("codel: %2i, x %2i, y %2i, DP: %2i, CC: %2i\t", pointer.codels[1], current_x, current_y, pointer.DP, pointer.CC);
		// printf("bumped: %i\n", bumps);
	}

	
	int stack[STACK_MAX_SIZE];




	// print_color_matrix(height, width, matrix);
	// print_2d_int(height, width, map);
	// print_codel_array_colors(codel_array, n_of_codels);
	// print_codel_array_corner_points(codel_array, n_of_codels);

	for (int i = 2; i < n_of_codels; i++)
		free(codel_array[i]);

	free_2d_colors(height, width, matrix);
	return 0;
}

