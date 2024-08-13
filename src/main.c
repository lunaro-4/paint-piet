#include "headers.h"
#include "png.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>



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




	struct pointer pointer = {DP_RIGHT, CC_LEFT};




	print_color_matrix(height, width, matrix);
	// print_2d_int(height, width, map);
	// print_codel_array_colors(codel_array, n_of_codels);
	// print_codel_array_corner_points(codel_array, n_of_codels);

	for (int i = 2; i < n_of_codels; i++)
		free(codel_array[i]);

	free_2d_colors(height, width, matrix);
	return 0;
}

