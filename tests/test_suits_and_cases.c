#include "test_defs.h"
#include <check.h>

void fill_parsing_cases();
void fill_colors_cases();

Suite * parameter_parsing (void)
{
	fill_parsing_cases();

	Suite *s;
	TCase *tc_core;

	s = suite_create("File");

	tc_core = tcase_create("Core");

	// tcase_add_test(tc_core, test_one_parameter_parsing);
	tcase_add_loop_test(tc_core, test_height_and_width_parsing, 0, (sizeof parsing_cases / sizeof parsing_cases[0]));
	suite_add_tcase(s, tc_core);

	return s;
}

Suite * color_parsing (void)
{
	fill_colors_cases();

	Suite *s = suite_create("Colors");
	TCase *tc_core = tcase_create("Colors_cases");

	tcase_add_loop_test(tc_core, test_color_matrix, 0, 0);

	return s;
}



struct parsing_case* new_parsing_case(int height, int width, char *filename)
{
	struct parsing_case *p_case;
	p_case = malloc(sizeof(struct parsing_case));
	p_case->height = height;
	p_case->width = width;
	strcpy(p_case->file_name, filename);
	return p_case;
}

void fill_parsing_cases()
{

	struct parsing_case 
		par_case_0 = *new_parsing_case(29, 30, "HelloWorld.png"),
		par_case_1 = *new_parsing_case(4, 9, "Add.png"),
		par_case_2 = *new_parsing_case(29, 30, "ColorError.png"),
		par_case_3 = *new_parsing_case(7, 14, "Countdown.png"),
		par_case_4 = *new_parsing_case(3, 7, "DivideByZero.png"),
		par_case_5 = *new_parsing_case(2, 4, "Endless.png"),
		par_case_6 = *new_parsing_case(7, 19, "StackRoll.png");
	parsing_cases[0] = par_case_0;
	parsing_cases[1] = par_case_1;
	parsing_cases[2] = par_case_2;
	parsing_cases[3] = par_case_3;
	parsing_cases[4] = par_case_4;
	parsing_cases[5] = par_case_5;
	parsing_cases[6] = par_case_6;
}

void fill_colors_cases()
{						 /* RED GREEN BLUE */
	struct color color_1 = {0xff, 0x0, 0x0},
				 color_2 = {0xff, 0xff, 0xff},
				 color_3 = {0x0, 0x0, 0x0},
				 color_4 = {0x0, 0x0, 0x0},
				 color_5 = {0x0, 0x0, 0x0},
				 color_6 = {0x0, 0x0, 0x0},
				 color_7 = {0x0, 0x0, 0x0},
				 color_8 = {0x0, 0x0, 0x0};
	// colors_cases[1];
	static struct colors_case case_one = {
		{
			{0xff, 0x0, 0x0},
			{0xff, 0xff, 0xff},
			{0x0, 0x0, 0x0},
			{0x0, 0x0, 0x0},
			{0x0, 0x0, 0x0},
			{0x0, 0x0, 0x0},
			{0x0, 0x0, 0x0},
			{0x0, 0x0, 0x0}
		},
		"Endless.png"} ;
	colors_cases[0] = case_one;
}

