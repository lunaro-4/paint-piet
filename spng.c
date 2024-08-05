#include <stdio.h>
#include <spng.h>
#include "custom_utils.c"

#define TRUE 1
#define FALSE 0

const char *color_type_str(enum spng_color_type color_type)
{
    switch(color_type)
    {
        case SPNG_COLOR_TYPE_GRAYSCALE: return "grayscale";
        case SPNG_COLOR_TYPE_TRUECOLOR: return "truecolor";
        case SPNG_COLOR_TYPE_INDEXED: return "indexed color";
        case SPNG_COLOR_TYPE_GRAYSCALE_ALPHA: return "grayscale with alpha";
        case SPNG_COLOR_TYPE_TRUECOLOR_ALPHA: return "truecolor with alpha";
        default: return "(invalid)";
    }
}

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

	const char * color_name = color_type_str(ihdr.color_type);

	printf("width: %u\n"
			"height: %u\n"
			"bit depth: %u\n"
			"color type: %u - %s\n",
			ihdr.width, ihdr.height, ihdr.bit_depth, ihdr.color_type, color_name);
	printf("compression method: %u\n"
			"filter method: %u\n"
			"interlace method: %u\n",
			ihdr.compression_method, ihdr.filter_method, ihdr.interlace_method);

	unsigned int *image = NULL;
	size_t image_size, image_width;
	int fmt = SPNG_FMT_PNG;

	spng_decoded_image_size(ctx, fmt, &image_size);
	image = malloc(image_size);

	void *out;
	size_t len;

	spng_decode_image(ctx, image, image_size, fmt, 0);

	// printf("%d\n", (sizeof *image / sizeof *image[0]));
	// printarr_1_hex( (int *) image);

	unsigned int * image_ptr = image, counter = 0;
	int count_6b = 0, count_8b = 0;
	
	// printf("%8x\t", *image_ptr);
	// while (*image_ptr++ != '\0') 
	// {
	// 		printf("%8x\t", *image_ptr);
	// 	if (*image_ptr >= 65500 && *image_ptr <= 16777216) 
	// 	{
	// 		counter++;
	// 		// printf("%x\t", *image_ptr);
	// 		if (*image_ptr == 4278190335) count_8b++;
	// 		if (*image_ptr == 16711680) count_6b++;
	//
	// 	}
	// 	if (*image_ptr > 4278190080) 
	// 	{
	// 		// printf("%x\t", *image_ptr);
	// 		count_8b++;
	// 	}
	// }
	//
	// printf("\n%i\n", counter);
	// printf("6b: %i\n", count_6b);
	// printf("8b: %i\n", count_8b);

	while (TRUE) 
	{
		printf("%8x\t", *image_ptr);
		image_ptr++;
		if (*image_ptr == '\0') break;
		counter++;

		// if (counter %2 == 0) putchar('\n');

	}

	return 0;
}
