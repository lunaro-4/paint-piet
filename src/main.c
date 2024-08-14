#include "headers.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define STACK_MAX_SIZE 200
#define MAX_COLOR 0xff
#define MID_COLOR 0x00


enum piet_hue {
	RED = 0, YELLOW = 1 , GREEN = 2 , CYAN = 3, BLUE = 4, MAGENTA = 5
};

enum piet_light {
	LIGHT, NORMAL, DARK
};

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

