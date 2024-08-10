#include "headers.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>




/* void append_point(struct point *array, struct point value)
{
	int arr_len = 0, i = 0;
	while (array + i != NULL)
	{
		arr_len++;
		i++;
	}
	struct point tmp_arr[arr_len+1];
	for (i = 0; i < arr_len; i++)
		tmp_arr[i] = array[i];
	free(array);
	array = malloc(arr_len+1 * sizeof(struct point));
	for (i = 0; i < arr_len; i++)
		array[i] = tmp_arr[i];
	array[arr_len] = value;
	
} */


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

	png_bytepp rows;
	get_rows(fptr, &rows);
	struct color *matrix[height][width];

	for (int i = 0; i < height; i++) {
        for (int j = 0; j < width  ; j++ ) {
			static struct color *c;
			c = malloc(sizeof(struct color));
			matrix[i][j] = c;
		}
	}

	create_matrix(rows, width, height, matrix);
	// print_color_matrix(height, width, matrix);

	int map[height][width], n_of_codels;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			map[y][x] = -1;
		}
	}
	struct color *codel_array[CODEL_ARRAY_SIZE];
	fill_2d_map(height, width, map, matrix, &n_of_codels, codel_array);


	print_2d_int(height, width, map);
	for (int i = 2; i < n_of_codels; i++)
		printf("codel_index: %2i R: %2x, G: %2x, B: %2x\t", i, codel_array[i]->red, codel_array[i]->green, codel_array[i]->blue);
	// printf("\n%i\n", n_of_codels);


	free_2d_colors(height, width, matrix);
	return 0;
}

