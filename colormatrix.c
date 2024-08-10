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
		// putchar('\n');
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
void test_nerby(int y, int x, int height, int width, int codel_index, int map[][width], struct color *matrix[][width])
{
	/* move across a board and mark points as visited */
	if (map[y][x] == -1) map[y][x] = codel_index;
	int around[4][2] = {
		{y, x + 1},
		{y + 1, x},
		{y, x - 1},
		{y - 1, x}
	};
	char message[100];
	
	for (int i = 0; i < 4; i++)
	{ 
		int new_y = around[i][0], new_x = around[i][1];
		bool is_in_height =
			new_y < height && new_y >= 0;
		bool is_in_width =
			new_x < width && new_x >= 0;
		bool is_valid_check_target = false;
		// if (y == 9 && x == 29) printf("i: %i, new_x: %i, new_y: %i, ii_h: %i, ii_w: %i\n", i, new_x, new_y, is_in_height, is_in_width); 
		if (is_in_height && is_in_width )
			is_valid_check_target = is_same_color(matrix[y][x], matrix[new_y][new_x]) && map[new_y][new_x] == -1;
		// else return;
		if (is_in_height && is_in_width && is_valid_check_target)
			test_nerby(new_y, new_x, height, width, codel_index, map, matrix);
	
	}
	
}

void fill_2d_map(int height, int width, int map[][width], struct color *matrix[][width], int *n_of_codels, struct color *codel_array[])
{
	int local_n_of_codels = 1;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map[y][x] != -1) continue;

			struct color *mat_col = matrix[y][x];
			if (!mat_col) { perror("Bad color"); return; }

			if (is_black(mat_col)) map[y][x] = BLACK_INDEX; 
			else if(is_white(mat_col)) map[y][x] = WHITE_INDEX;
			else 
			{
				local_n_of_codels++;
				test_nerby(y, x, height, width, local_n_of_codels, map, matrix);
				codel_array[local_n_of_codels] = matrix[y][x];
			}
		}
	}
	*n_of_codels = local_n_of_codels;

}
