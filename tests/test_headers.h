#ifndef INCLUDED
#define INCLUDED



#include <check.h>
#include <string.h>
#include "../headers.h"

struct parsing_case {
	int height;
	int width; 
	char file_name[100];
};

struct parsing_case* new_parsing_case(int height, int width, char *filename);

Suite * parameter_parsing (void);
// Suite * parameter_parsing (void);
// Suite * parameter_parsing (void);


void fill_parsing_cases();




#endif // !INCLUDED
