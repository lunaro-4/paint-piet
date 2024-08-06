#include "structs.h"
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include "custom_utils.h"


void create_matrix(png_bytepp png_rows,  int width, int height, struct color *matrix[height][width]);

void get_rows(FILE *fptr, png_bytepp *rows);

void get_width_and_height(FILE *fptr, int* width, int* height);

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

	int width, height;
	get_width_and_height(fptr, &width, &height);

	fclose(fptr);
	fptr = fopen(file_path, "r");

	png_bytepp rows;
	get_rows(fptr, &rows);
	struct color *matrix[height][width];

	for (int i = 0; i < height; i++) {
        for (int j = 0; j < width  ; j++ ) {
			static struct color *c;
			c = malloc(sizeof(struct color));
			matrix[i][j] = c;
		}
	}

	create_matrix(rows, width, height, matrix);
	print_color_matrix(height, width, matrix);

	return 0;
}

void create_matrix(png_bytepp png_rows,  int width, int height, struct color *matrix[height][width])
{
	for (int i = 0; i < height; i++) {
        for (int j = 0; j+2 < width * 3 ; j += 3) {
			struct color *c = matrix[i][j/3];
			c->red = (int) png_rows[i][j];
			c->green = png_rows[i][j+1];
			c->blue = png_rows[i][j+2];
        }   
    }
}

void get_rows(FILE *fptr, png_bytepp *rows)
{    png_structp pngptr =
        png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop pnginfo = png_create_info_struct(pngptr);
    png_set_palette_to_rgb(pngptr);
	png_const_inforp *info_ptr;
    png_init_io(pngptr, fptr);
    png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);
    *rows = png_get_rows(pngptr, pnginfo);
}

void get_width_and_height(FILE *fptr, int* width, int* height)
{
	// 8 byte PNG metadata 
	get_chunk_value(fptr);
	get_chunk_value(fptr);
	// chunk start
	get_chunk_value(fptr);
	// metadata IHDR flag
	get_chunk_value(fptr);
	*width = get_chunk_value(fptr);
	*height = get_chunk_value(fptr);
}
