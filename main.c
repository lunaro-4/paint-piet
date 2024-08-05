#include <png.h>
#include <stdio.h>


int main(int argc, char *argv[])
{

	char* file_path;

	if (argc > 1) {
		file_path = argv[1];
	}
	else {
		file_path = "in.png";
	}
	FILE *fptr = fopen(file_path, "r");

    png_structp pngptr =
        png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop pnginfo = png_create_info_struct(pngptr);
    png_set_palette_to_rgb(pngptr);
	png_const_inforp *info_ptr;
	png_uint_32 *width, *height;
	
	// int bit_depth, color_type, interlace_method, compression_method, filter_method;
	// png_read_info(pngptr, info_ptr);
	// png_get_IHDR(pngptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_method, NULL, NULL);

    png_init_io(pngptr, fptr);
	png_bytepp rows;
    png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);
    rows = png_get_rows(pngptr, pnginfo);

	for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8 * 3; j += 3) {
            printf("%d %d %d ", rows[i][j], rows[i][j + 1], rows[i][j + 2]);
        }   
        printf("\n");
    }

	return 0;
}
