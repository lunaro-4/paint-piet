#include <png.h>
#include <stdio.h>
#include "custom_utils.c"


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
	int width, height;
	width = get_chunk_value(fptr);
	height = get_chunk_value(fptr);

	fclose(fptr);
	fptr = fopen(file_path, "r");

    png_structp pngptr =
        png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop pnginfo = png_create_info_struct(pngptr);
    png_set_palette_to_rgb(pngptr);
	png_const_inforp *info_ptr;
    png_init_io(pngptr, fptr);
	png_bytepp rows;
    png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);
    rows = png_get_rows(pngptr, pnginfo);
	for (int i = 0; i < height; i++) {
        for (int j = 0; j+3 <= width * 3 ; j += 3) {
            printf("R:%2x G:%2x B:%2x ", rows[i][j], rows[i][j + 1], rows[i][j + 2]);
        }   
        printf("\n");
    }

	return 0;
}
