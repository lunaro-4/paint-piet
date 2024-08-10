#include "../headers.h"
#include "test_headers.h"
#include "../logger/logger.h"
#include <check.h>
#include <stdio.h>
#include <string.h>
// int test_one_parameter_parsing(FILE *input, int assert_height, int assert_width);



int main(int argc, char *argv[])
{ 
	remove(LOGFILE);

	bool params_flag = false, colors_flag = false;
	while (--argc > 0)
	{
		argv++;
		printf("%i\n", strcmp(*argv, "all"));
		if (strcmp(*argv, "all") == 0)
		{
			params_flag = true;
			colors_flag = true;
			break;
		}
		else if (strcmp(*argv, "params") == 0) params_flag = true;
		else if (strcmp(*argv, "colors") == 0) colors_flag = true;
	}

	Suite *null_suite = NULL;
	SRunner *sr;

	sr = srunner_create(null_suite);
	if (params_flag) srunner_add_suite(sr, parameter_parsing());
	if (colors_flag) srunner_add_suite(sr, color_parsing());


	srunner_run_all(sr, CK_NORMAL);

	int fails_and_errors;
	fails_and_errors = srunner_ntests_failed(sr);
	
	// struct TestResult **results;
	// results = srunner_failures(sr);

	return fails_and_errors;
}

