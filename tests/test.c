#include "../headers.h"
#include "test_headers.h"
#include "test_defs.h"
// int test_one_parameter_parsing(FILE *input, int assert_height, int assert_width);



int main(int argc, char *argv[])
{ 
	int total_failed;
	Suite *s;
	SRunner *sr;

	s = parameter_parsing();
	sr = srunner_create(s);


	fill_parsing_cases();
	
	srunner_run_all(sr, CK_VERBOSE);

	total_failed = srunner_ntests_failed(sr);

	srunner_free(sr);

	return (total_failed == 0) ? 0 : 1;
}

