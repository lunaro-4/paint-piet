#include <stdio.h>
#include <spng.h>


int main(int argc, char *argv[])
{
	char* file_path;
	spng_ctx * ctx = NULL;

	if (argc > 1) {
		file_path = argv[1];
	}
	else {
		file_path = "in.png";
	}
	FILE *fptr = fopen(file_path, "r");

	ctx = spng_ctx_new(0);
	spng_set_png_file(ctx, fptr);

	struct spng_ihdr ihdr;
	spng_get_ihdr(ctx, &ihdr);

	// const int * color_name = color_type_str(ihdr.color_type);

	printf("width: %u\n"
			"height: %u\n"
			"bit depth: %u\n"
			"color type: %u - 0\n",
			ihdr.width, ihdr.height, ihdr.bit_depth, ihdr.color_type);


	return 0;
}
