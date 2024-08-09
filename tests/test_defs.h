#include "test_headers.h"
#include "../logger/logger.h"
#include <check.h>
#include <stdio.h>
#include <string.h>

#ifndef GET_FILE
#define GET_FILE 
void get_file(FILE *fptr, char file_name[])
{
	char rel_path[1000];
	char *abs_path = realpath("..", NULL);
	sprintf(rel_path, "%s%s%s", abs_path, "/example/", file_name);
	fptr = fopen(rel_path, "r");
	if (!fptr) 
	{
		char msg[1030];
		sprintf(msg, "Error opening file: %s", rel_path);
		logger(msg);
		// logger("Error opening file!");
	}
	free(abs_path);
}

#endif

#ifndef DEFS
#define DEFS
// static struct parsing_case parsing_cases[7];


START_TEST(test_height_and_width_parsing)
{
    struct parsing_case test_case = parsing_cases[_i];
	static FILE* fptr;
	get_file(fptr, test_case.file_name);

	int height, width;
	get_height_and_width(fptr, &height, &width);

	int assert_height = test_case.height, assert_width = test_case.width;
	
	// printf("%s", rel_path);
	int width_diff = width-assert_width, height_diff = height-assert_height;
	ck_assert_int_eq(width_diff, 0);
	ck_assert_int_eq(width_diff, height_diff);
}
END_TEST

START_TEST(test_color_matrix)
{
	struct colors_case test_case = colors_cases[_i];
	static FILE* fptr;
	get_file(fptr, test_case.file_name);

	int height, width;
	get_height_and_width(fptr, &height, &width);

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

	int fails;
	create_matrix(rows, width, height, matrix);

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			fails += !is_same_color(matrix[h][w], &test_case.colors_array[w+h*width]);
		}
	}
	ck_assert_int_eq(fails, 0);
}
END_TEST



#endif // !DEFS
