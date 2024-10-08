#include "test_headers.h"
#include <string.h>
#include "logger.h"
// int test_one_parameter_parsing(FILE *input, int assert_height, int assert_width);



int main(int argc, char *argv[])
{ 

	remove(LOGFILE);


	bool params_flag = false,
		 colors_flag = false,
		 compare_flag = false,
		 codels_flag = false;
	while (--argc > 0)
	{
		argv++;
		printf("%i\n", strcmp(*argv, "all"));
		if (strcmp(*argv, "all") == 0)
		{
			params_flag = true;
			colors_flag = true;
			compare_flag = true;
			codels_flag = true;
			break;
		}
		else if (strcmp(*argv, "params") == 0) params_flag = true;
		else if (strcmp(*argv, "colors") == 0) colors_flag = true;
		else if (strcmp(*argv, "compare") == 0) compare_flag = true;
		else if (strcmp(*argv, "codels") == 0) codels_flag = true;
	}

	Suite *null_suite = NULL;
	SRunner *sr;

	sr = srunner_create(null_suite);
	if (params_flag) srunner_add_suite(sr, parameter_parsing());
	if (colors_flag) srunner_add_suite(sr, color_parsing());
	if (compare_flag) srunner_add_suite(sr, color_comparison());
	if (codels_flag) srunner_add_suite(sr, codels());


	srunner_run_all(sr, CK_NORMAL);

	int fails_and_errors;
	fails_and_errors = srunner_ntests_failed(sr);
	
	// struct TestResult **results;
	// results = srunner_failures(sr);

	return fails_and_errors;
}

