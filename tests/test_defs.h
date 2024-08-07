#include "test_headers.h"

#ifndef DEFS
#define DEFS
static struct parsing_case parsing_cases[7];


START_TEST(test_height_and_width_parsing)
{

    struct parsing_case test_case = parsing_cases[_i];
	static FILE* fptr;
	char rel_path[10000];
	sprintf(rel_path, "%s/%s", "../example",test_case.file_name);
	char *abs_path = realpath(rel_path, NULL);

	fptr = fopen(rel_path, "r");
	int height, width;
	get_height_and_width(fptr, &height, &width);

	int assert_height = test_case.height, assert_width = test_case.width;
	
	printf("%s", rel_path);
	int width_diff = width-assert_width, height_diff = height-assert_height;
	ck_assert_int_eq(width_diff, 0);
	ck_assert_int_eq(width_diff, height_diff);
}
END_TEST



#endif // !DEFS
