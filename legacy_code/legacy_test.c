#include "../headers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PASS 1
#define FAIL 0

#define COMPARE(expect, assert) if (expect != assert) raise_on_error();



#define test_dir ;
#define png_0 test_dir"HelloWorld.png"
#define png_0 test_dir"HelloWorld.png"


unsigned char to_raise = 0;
void raise_on_error();

unsigned int tests_count_local = 0, tests_count_global = 0, test_fails_local = 0, test_fails_global = 0;
void print_test_stats();

void test_creation();
int test_one_parameter_parsing(FILE *input, int assert_height, int assert_width);
int test_all_parameter_parsing();

void read_dir(char *path, char *file_names[], int *count_files);
FILE* open_file(char *name);



int main(int argc, char *argv[])
{ 
	int count_files = 0;
	char *file_names[10000];
	// read_dir("/home/lunaro/git/paint-piet/example", file_names, &count_files);
	//
	char **argv_ptr = argv;

	while (1)
	{
		if (strcmp(*argv_ptr, "raise") == 0) 
		{
			to_raise = 1;
			break;
		} 
		argv_ptr++;
		if (*argv_ptr == NULL) break;
	}

	// for (int i = 0; i < count_files; i++)
	// {
	// 	printf("%s ", file_names[i]);
	// 	printf("%d\n", count_files);
	// }
	open_file("HelloWorld.png");

	test_all_parameter_parsing();
	print_test_stats();
	return 0;
}

int test_all_parameter_parsing()
{
	tests_count_local = 0;
	int error_count = 0;
	FILE *fptr;

    test_one_parameter_parsing(open_file("HelloWorld.png"), 30, 29);
	// assert(test_one_parameter_parsing(fopen(png_1, "r"), 31, 29) == 1);

	printf("\nparameter_parsing done: %i,  failed: %i", tests_count_local, test_fails_local);
	return PASS;
}


int test_one_parameter_parsing(FILE *input, int assert_height, int assert_width)
{
	tests_count_local++;
	tests_count_global++;
	int height, width;
	get_width_and_height(input, &height, &width);

	if (width == assert_width && height == assert_height) return PASS;
	else 
	{
		printf("\tGot:\t\t\t\tExpected:\n\twidth: %i, height: %i\t|\twidth: %i, height: %i\n", width, height, assert_width, assert_height); 
		raise_on_error();
		return FAIL;
	}

	return PASS;
}

void read_dir(char *path, char *file_names[], int *count_files)
{
	printf("%s\n", path);
	DIR *d;
	struct dirent *dir;
	int i = 0;
	d = opendir(path);
	if (d)
	{ 
		printf("fire");
		while ((dir = readdir(d)) != NULL)
		{ 
			if (dir->d_type != DT_DIR) (*count_files)++;
		
		}
	}
	// dir_files = malloc(count_files * sizeof(FILE));
	closedir(d);
	d = opendir(path);
	if (d)
	{ 
		while ((dir = readdir(d)) != NULL)
		{ 
			if (dir->d_type==DT_REG)
			{
				file_names[i] = (char*) malloc(strlen(dir->d_name)+1);
				strncpy(file_names[i], dir->d_name, strlen(dir->d_name));
				i++;
			}
		}
	}
}

void print_test_stats()
{
	printf("\nTotal tests: %i\t ==Successful: %i==\t --Fails: %i--", tests_count_global, tests_count_global- test_fails_global, test_fails_global);
}

void raise_on_error()
{
	test_fails_global++;
	if (to_raise) assert(0);
}
FILE* open_file(char *name)
{
	static FILE* fptr;
	// HACK
	char rel_path[10000];
	sprintf(rel_path, "%s/%s", "../example", name);
	char *abs_path = realpath(rel_path, NULL);

	// printf("%s\n", strcat(abs_path, name));
	fptr = fopen(abs_path, "r");
	return fptr;
}
