#ifndef INCLUDED
#define INCLUDED



#include "paint-piet-runtime.h"
#include <check.h>
#include "project-headers.h"

static struct parsing_case {
	int height;
	int width; 
	char file_name[100];
} parsing_cases[7];

static struct colors_case {
	struct color colors_array[100000];
	char file_name[100];
} colors_cases[3];

static struct codels_case {
	struct codel codels[100];
	char file_name[100];
} codels_cases[1];

struct parsing_case* new_parsing_case(int height, int width, char *filename);

Suite * parameter_parsing (void);
Suite * color_parsing (void);
Suite * color_comparison (void);
Suite * codels (void);
// Suite * parameter_parsing (void);



#endif // !INCLUDED
