#include "../headers.h"
#include <check.h>
// int test_one_parameter_parsing(FILE *input, int assert_height, int assert_width);

START_TEST(test_one_parameter_parsing)

{
	static FILE* fptr;
	// HACK
	char rel_path[10000];
	sprintf(rel_path, "%s/%s", "../example", "HelloWorld.png");
	char *abs_path = realpath(rel_path, NULL);

	// printf("%s\n", strcat(abs_path, name));
	fptr = fopen("/home/lunaro/git/paint-piet/example/HelloWorld.png", "r");
	int height, width;
	get_width_and_height(fptr, &height, &width);

	int assert_width = 30, assert_height = 29;

	// if (width == assert_width && height == assert_height) return 1;
	ck_assert(width == assert_width && height == assert_height);
}
END_TEST

Suite * read_file_sute (void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("File");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_one_parameter_parsing);
	suite_add_tcase(s, tc_core);

	return s;
}


int main(int argc, char *argv[])
{ 
	int total_failed;
	Suite *s;
	SRunner *sr;

	s = read_file_sute();
	sr = srunner_create(s);


	srunner_run_all(sr, CK_VERBOSE);

	total_failed = srunner_ntests_failed(sr);

	srunner_free(sr);

	return (total_failed == 0) ? 0 : 1;
}
