#include "project-headers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define CODEL_ARRAY_SIZE 500


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

	if (fptr == NULL) {
		perror("File error:");
		return 1;
	}

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
	int stack[STACK_MAX_SIZE], *stack_ptr = stack;
	int debug_action_count = 0;
	const int DEBUG_FIRE = -1;
	while (bumps < 8) // DP should see all 4 directions
	{
		debug_action_count++;
		bool white_skip = false, white_encountered = process_pointer(&current_y, &current_x, height, width, map, &pointer, codel_array, &bumps);
		if (white_encountered)
		{
			white_skip = true;
			continue;
		}
		if (white_skip)
		{
			white_skip = false;
			continue;
		}
		if (bumps == 0)
		{
			int hue_steps, light_steps;
			struct codel *from = codel_array[pointer.codels[0]], *to = codel_array[pointer.codels[1]];
			count_steps(&from->color, &to->color, &hue_steps, &light_steps);
			

			if (DEBUG_FIRE > -1 && debug_action_count >= DEBUG_FIRE)
			{
				printf("\ncodel.id: from: %i, to: %i\n", pointer.codels[0], pointer.codels[1]);
				printf("codel.size: from: %i, to: %i\n", from->size, to->size);
				_piet_debug(hue_steps, light_steps);
				print_int_array(stack, stack_ptr - stack);
			}
			
			process_move(hue_steps, light_steps, from->size, &pointer, stack, &stack_ptr);
		}
		// printf("codel: %2i, x %2i, y %2i, DP: %2i, CC: %2i\t", pointer.codels[1], current_x, current_y, pointer.DP, pointer.CC);
		// printf("bumped: %i\n", bumps);
	}

	





	// print_color_matrix(height, width, matrix);
	// print_2d_int(height, width, map);
	// print_codel_array_colors(codel_array, n_of_codels);
	// print_codel_array_corner_points(codel_array, n_of_codels);

	for (int i = 2; i < n_of_codels; i++)
		free(codel_array[i]);

	free_2d_colors(height, width, matrix);
	return 0;
}
#define CODEL_ARRAY_SIZE 500

