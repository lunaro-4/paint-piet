#include "headers.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>


void test_nerby(int y, int x, int height, int width, int codel_index, int map[height][width], struct color **matrix)
{
	// move across a board and mark points as visited
	map[y][x] = codel_index;
	int around[4][2] = {
		{y, x + 1},
		{y + 1, x},
		{y, x - 1},
		{y - 1, x}
	};
	
	for (int i = 0; i < 4; i++)
	{ 
		int new_y = around[i][0], new_x = around[i][1];
		bool is_in_height =
			new_y < height && new_y >= 0;
		bool is_in_width =
			new_x < height && new_x >= 0;
		bool is_valid_check_target =
			is_same_color(&matrix[y][x], &matrix[new_y][new_x]) &&
			map[new_y][new_x] == -1;
		if (is_in_height && is_in_width && is_valid_check_target)
			test_nerby(new_y, new_x, height, width, codel_index, map, matrix);
	}
}

void fill_2d_map(int height, int width, struct color **matrix)
{
	int map[height][width];
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			map[y][x] = -1;
		}
	}
	int n_of_codels = 1;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			struct color *mat_col = &matrix[y][x];
			if (map[y][x] == -1)
			{
				if (is_black(mat_col)) map[y][x] = BLACK_INDEX; 
				else if(is_white(mat_col)) map[y][x] = WHITE_INDEX;
				else 
				{
					n_of_codels++;
					test_nerby(y, x, height, width, n_of_codels, map, matrix);
				}
			}
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%i\t", map[i][j]);
		}
		putchar('\n');
	}

}

void append_point(struct point *array, struct point value)
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
	
}


void parse_codels(int height, int width, struct color *matrix )
{
	uint codel_count;


	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			while (true)
			{
				
			}
		}
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
	print_color_matrix(height, width, matrix);

	fill_2d_map(height, width, *matrix);

	return 0;
}

