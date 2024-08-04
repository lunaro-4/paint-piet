#include <stdio.h>
// #include <png.h>

int main(int argc, char *argv[])
{
	int character;

	char* file_path;

	if (argc > 1) 
	{
		file_path = argv[1];
	}
	else {
		file_path = "in.png";
	}
	FILE *fptr = fopen(file_path, "r");
	if (fptr == NULL)
	{
		perror("error openining file");
		return 1;
	}
	while ((character = fgetc(fptr)) != EOF) 
	{
		printf("%x ", character);
	}

	return 0;
}
