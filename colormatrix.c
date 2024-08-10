#include "headers.h"


void create_matrix(png_bytepp png_rows,  int width, int height, struct color *matrix[height][width])
{
	for (int i = 0; i < height; i++) {
        for (int j = 0; j+2 < width * 3 ; j += 3) {
			struct color *c = matrix[i][j/3];
			c->red = (int) png_rows[i][j];
			c->green = png_rows[i][j+1];
			c->blue = png_rows[i][j+2];
			// printf("R: %2x, G: %2x, B: %2x  ", c->red, c->green, c->blue);
        }   
		putchar('\n');
    }
}

void get_rows(FILE *fptr, png_bytepp *rows)
{  
	png_structp pngptr =
		png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop pnginfo = png_create_info_struct(pngptr);
    png_set_palette_to_rgb(pngptr);
	png_const_inforp *info_ptr;
    png_init_io(pngptr, fptr);
    png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);
    *rows = png_get_rows(pngptr, pnginfo);
}

void get_height_and_width(FILE *fptr, int* height, int* width )
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
