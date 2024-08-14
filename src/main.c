#include "headers.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define STACK_MAX_SIZE 200

void pointer_bump (struct pointer *pointer)
{
	if (pointer->cc_switched){
		switch (pointer->DP) {
			case DP_RIGHT:
				pointer->DP = DP_DOWN;
				break;
			case DP_DOWN:
				pointer->DP = DP_LEFT;
				break;
			case DP_LEFT:
				pointer->DP = DP_UP;
				break;
			case DP_UP:
				pointer->DP = DP_RIGHT;
		} // pointer->CC = CC_RIGHT; // apparantly, it should not reset the CC on DP change
	}
	else 
		switch (pointer->CC) {
			case CC_LEFT:
				pointer->CC = CC_RIGHT;
				break;
			case CC_RIGHT:
				pointer->CC = CC_LEFT;
				break;
		}

	pointer->cc_switched = !pointer->cc_switched;
}

bool move_pointer(int *y, int *x, int *new_y, int *new_x, int height, int width, int map[][width], enum direction *dp, enum moves *cc, int *bumps) 
{
	switch (*dp) {
		case DP_RIGHT:
			*new_y = *y;
			*new_x = *x + 1;
			break;
		case DP_DOWN:
			*new_y = *y + 1;
			*new_x = *x;
			break;
		case DP_LEFT:
			*new_y = *y;
			*new_x = *x - 1;
			break;
		case DP_UP:
			*new_y = *y - 1;
			*new_x = *x;
			break;
	}

	if (*new_y < 0 || *new_y >= height || *new_x < 0 || *new_x >= width ||
			map[*new_y][*new_x] == BLACK_INDEX)
	{
		(*bumps)++;
		*new_y = *y;
		*new_x = *x;
		return true;
	}
	return false;
}

void process_pointer(int *y, int *x, int height, int width, int map[][width], struct pointer *pointer, struct codel *codel_array[], int *bumps)
{

	int new_y, new_x;

	enum direction *dp = &pointer->DP;
	enum moves *cc = &pointer->CC;
	bool bumped = move_pointer(y, x, &new_y, &new_x, height, width, map, dp, cc, bumps);
	if (bumped) pointer_bump(pointer);

	int current_codel_id = map[*y][*x];
	int next_codel_id = map[new_y][new_x];


	if (!bumped && next_codel_id == WHITE_INDEX)
	{
		perror("Its white!");
		bool is_white = true;
		int local_x = *x, local_y = *y;
		while (is_white)
		{
			bool bumped = move_pointer(&local_y, &local_x, &new_y, &new_x, height, width, map, dp, cc, bumps);
			if (bumped) pointer_bump(pointer);
			local_y = new_y;
			local_x = new_x;
			is_white = map[local_y][local_x] == WHITE_INDEX;
		} 
		// printf("whited x: %i, whited y: %i \t", local_x, local_y);
		*y = local_y;
		*x = local_x;
		return;
	}

	struct codel *chosen_codel;
	if (bumped)
	{
		chosen_codel =  codel_array[current_codel_id];
		// bumps++;
	}
	else 
	{
		chosen_codel =  codel_array[next_codel_id];
		pointer->codels[0] = current_codel_id;
		pointer->codels[1] = next_codel_id;
		*bumps = 0;
	}
	
	if (*dp == DP_RIGHT || *dp == DP_LEFT)
	{
		*x = chosen_codel->corner_points[*dp][0];
		*y = chosen_codel->corner_points[*dp][*cc];
	}
	else 
	{
		*y = chosen_codel->corner_points[*dp][0];
		*x = chosen_codel->corner_points[*dp][*cc];
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
		printf("codel: %2i, x %2i, y %2i, DP: %2i, CC: %2i\t", pointer.codels[1], current_x, current_y, pointer.DP, pointer.CC);
		printf("bumped: %i\n", bumps);
	}



	putchar('\n');

	// print_color_matrix(height, width, matrix);
	// print_2d_int(height, width, map);
	// print_codel_array_colors(codel_array, n_of_codels);
	// print_codel_array_corner_points(codel_array, n_of_codels);

	for (int i = 2; i < n_of_codels; i++)
		free(codel_array[i]);

	free_2d_colors(height, width, matrix);
	return 0;
}

