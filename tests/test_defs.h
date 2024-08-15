#include "test_headers.h"
#include "../logger/logger.h"
#include <check.h>
#include <stdio.h>
#include <string.h>
#define CODEL_ARRAY_SIZE 500

#ifndef GET_FILE
#define GET_FILE 
void get_file(FILE **fptr, char file_name[])
{
	char rel_path[1000];
	char *abs_path = realpath(".", NULL);
	// HACK
	char *is_in_tests = strstr(abs_path, "tests");
	if (is_in_tests) abs_path = realpath("..", NULL);
	// perror(abs_path);

	sprintf(rel_path, "%s%s%s", abs_path, "/example/", file_name);
	// perror(rel_path);
	*fptr = fopen(rel_path, "r");
	if (*fptr == NULL) 
	{
		char msg[1030];
		sprintf(msg, "Error opening file: %s", rel_path);
		perror(msg);
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
	int height, width;
	get_file(&fptr, test_case.file_name);

	if (!fptr) perror("Bad file");
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
	int height, width;
	get_file(&fptr, test_case.file_name);

	if (!fptr) perror("Bad file");
	get_height_and_width(fptr, &height, &width);

	fclose(fptr);
	get_file(&fptr, test_case.file_name);

	struct color *matrix[height][width];

	for (int i = 0; i < height; i++) {
        for (int j = 0; j < width  ; j++ ) {
			static struct color *c;
			c = malloc(sizeof(struct color));
			matrix[i][j] = c;
		}
	}

	int fails;
	create_matrix(fptr, width, height, matrix);

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

START_TEST(test_compare)
{
	struct color color_black = {0x0, 0x0, 0x0};
	struct color color_white = {0xff, 0xff, 0xff};
	struct color color_1 = {0xff, 0x0, 0x0};
	struct color color_2 = {0xff, 0xc0, 0xc0};
	struct color color_3 = {0x0, 0x0, 0xc0};
	struct color color_4 = {0xff, 0xc0, 0xc0};

	ck_assert(is_black(&color_black));
	ck_assert(is_white(&color_white));
	ck_assert(!is_black(&color_white));
	ck_assert(is_same_color(&color_2, &color_4));
	ck_assert(!is_same_color(&color_2, &color_1));
	ck_assert(!is_same_color(&color_1, &color_3));
	ck_assert(!is_same_color(&color_3, &color_black));

}
END_TEST

START_TEST(test_codels)
{
	struct codels_case test_case = codels_cases[_i];
	static FILE* fptr;
	int height, width;
	get_file(&fptr, test_case.file_name);

	if (!fptr) perror("Bad file");
	get_height_and_width(fptr, &height, &width);

	fclose(fptr);
	get_file(&fptr, test_case.file_name);

	struct color *matrix[height][width];

	for (int i = 0; i < height; i++) {
        for (int j = 0; j < width  ; j++ ) {
			static struct color *c;
			c = malloc(sizeof(struct color));
			matrix[i][j] = c;
		}
	}

	int fails = 0;
	create_matrix(fptr, width, height, matrix);
	
	int map[height][width], n_of_codels;

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			map[y][x] = -1;
	struct codel *codel_array[CODEL_ARRAY_SIZE];
	fill_2d_map(height, width, map, matrix, &n_of_codels, codel_array);
	
	find_codels_corner_points(height, width, map, codel_array);

	for (int n = 2; n < n_of_codels + 1; n++)
	{
		int (*points_real)[3] = codel_array[n]->corner_points;
		int (*points_assert)[3] = test_case.codels[n-2].corner_points;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
			{
				int expect = points_real[i][j], assert = points_assert[i][j];
				if (expect == assert )
					continue;
				char msg[200], * direction;
				switch (i) {
					case DP_RIGHT:
						direction = "RIGHT";
						break;
					case DP_DOWN:
						direction = "DOWN";
						break;
					case DP_LEFT:
						direction = "LEFT";
						break;
					case DP_UP:
						direction = "UP";
						break;
				}
				sprintf(msg, "Case %i fail at:\tCodel: %i, direction: %s, index: %i\t %i != %i", _i, n, direction, j, expect, assert);
				perror(msg);
				fails++;

			}
	}

	ck_assert_int_eq(fails, 0);




}
END_TEST

#endif // !DEFS
