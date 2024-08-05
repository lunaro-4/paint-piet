#include <stdio.h>


int get_chunk_value(FILE * fptr)
{
	int value = 0;
	for (char char_count = 0; char_count < 4; char_count++)
	{
		value += fgetc(fptr);
	}
	return value;
}

int main(int argc, char *argv[])
{
	int character;
	unsigned int char_count = 0;

	char* file_path;

	if (argc > 1) {
		file_path = argv[1];
	}
	else {
		file_path = "in.png";
	}

	FILE *fptr = fopen(file_path, "r");

	if (fptr == NULL) {
		perror("error openining file");
		return 1;
	}
	
	// 8 byte PNG metadata 
	get_chunk_value(fptr);
	get_chunk_value(fptr);
	// chunk start
	get_chunk_value(fptr);
	// metadata IHDR flag
	get_chunk_value(fptr);

	char chunk_count = 1;
	unsigned char chunk_value = 0;

	int width = 0, height = 0, b_depth = 0, color_type = 0, compression_method = 0, filter_method = 0, interlace_method = 0;
	
	width = get_chunk_value(fptr);
	height = get_chunk_value(fptr);
	b_depth = fgetc(fptr);
	color_type = fgetc(fptr);
	compression_method = fgetc(fptr);
	filter_method = fgetc(fptr);
	interlace_method = fgetc(fptr);

	printf("Width: %i\n", width);
	printf("Height: %i\n", height);
	printf("b_depth: %i\n", b_depth);
	printf("color_type: %i\n", color_type);
	printf("compression_method: %i\n", compression_method);
	printf("filter_method: %i\n", filter_method);
	printf("interlace_method: %i\n", interlace_method);
	while ((character = fgetc(fptr)) != EOF ) 
	{
		// printf("%x ", character);
		putchar(character);
		chunk_value += character;
		if (chunk_count < 4) {
			;
		} else {
			// printf("%i", chunk_value);
			chunk_value = 0;
			putchar('\t');
			chunk_count = 0;
		}
		chunk_count++;
	}

	return 0;
}
