#include "headers.h"
#include "png.h"
#include "pngconf.h"


void create_matrix(FILE *fptr,  int width, int height, struct color *matrix[height][width])
{
	png_structp pngptr =
		png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop pnginfo = png_create_info_struct(pngptr);
    png_set_palette_to_rgb(pngptr);
	png_inforp *info_ptr;
    png_init_io(pngptr, fptr);
    png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);
    png_bytepp png_rows = png_get_rows(pngptr, pnginfo);
	png_voidp vptr;

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
	png_destroy_read_struct(&pngptr, &pnginfo, &pnginfo);
}

void get_rows_and_matrix(FILE *fptr, png_bytepp *rows)
{  
	png_structp pngptr =
		png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop pnginfo = png_create_info_struct(pngptr);
    png_set_palette_to_rgb(pngptr);
	png_inforp *info_ptr;
    png_init_io(pngptr, fptr);
    png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);
    *rows = png_get_rows(pngptr, pnginfo);
	png_voidp vptr;
	png_free_data(pngptr, *info_ptr, PNG_FREE_ROWS, -1);
	
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


void test_nerby(int y, int x, int height, int width, int codel_index, int map[][width], struct color *matrix[][width], int *codel_size)
{
	/* move across a board and mark points as visited */
	if (map[y][x] == -1)
	{
		map[y][x] = codel_index;
		codel_size++;
	}
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
			test_nerby(new_y, new_x, height, width, codel_index, map, matrix, codel_size);
	
	}
	
}

void fill_2d_map(int height, int width, int map[][width], struct color *matrix[][width], int *n_of_codels, struct codel *codel_array[])
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
				struct codel *codel = malloc(sizeof(struct codel));
				int  codel_size;
				local_n_of_codels++;
				test_nerby(y, x, height, width, local_n_of_codels, map, matrix, &codel_size);
				codel->size = codel_size;
				codel->color = *mat_col;

				codel_array[local_n_of_codels] = codel;
			}
		}
	}
	*n_of_codels = local_n_of_codels;

}
void fill_corner_points (int y, int x, int height, int width, int corner_points[][3])
{
	corner_points[0][0] = 0;
	corner_points[0][1] = y;
	corner_points[0][2] = y;
	corner_points[1][0] = 0;
	corner_points[1][1] = x;
	corner_points[1][2] = x;
	corner_points[2][0] = height;
	corner_points[2][1] = y;
	corner_points[2][2] = y;
	corner_points[3][0] = width;
	corner_points[3][1] = x;
	corner_points[3][2] = x;
}

void compare_points (int y, int x, int corner_points[][3])
{
	// Rx [Ryr Ryl]
	if (x > corner_points[0][0]) {
		corner_points[0][0] = x;
		corner_points[0][1] = y;
		corner_points[0][2] = y;  
	} 
	else if (x == corner_points[0][0]) 
	{
		corner_points[0][1] = min(corner_points[0][1], y);
		corner_points[0][2] = max(corner_points[0][2], y); 
	}
	///
	//	Dy [Dxr Dxl]
	///
	if (y > corner_points[1][0]) {
		corner_points[1][0] = y;
		corner_points[1][1] = x;
		corner_points[1][2] = x;  
	} else
		if (y == corner_points[1][0]) 
		{
			corner_points[1][1] = max(corner_points[1][1], x);
			corner_points[1][2] = min(corner_points[1][2], x); 
		}
	///
	//	Lx [Lyr Lyl]
	/// 
	if (x < corner_points[2][0]) {
		corner_points[2][0] = x;
		corner_points[2][1] = y;
		corner_points[2][2] = y;  
	} else
		if (x == corner_points[2][0]) 
		{
			corner_points[2][1] = max(corner_points[2][1], y);
			corner_points[2][2] = min(corner_points[2][2], y); 
		}
	/// 
	//  Uy [Uxr Uxl
	///
	if (y < corner_points[3][0]) {
		corner_points[3][0] = y;
		corner_points[3][1] = x;
		corner_points[3][2] = x;  
	} else
		if (y == corner_points[3][0]) 
		{
			corner_points[3][1] = min(corner_points[3][1], y);
			corner_points[3][2] = max(corner_points[3][2], y); 
		}

}
void resolve_codel (int height, int width, int y, int x, int map[][width], struct codel *codel, int codel_index)
{
	/* corner_points scheme:
	   0 X+ => Y- Y+
	   1 Y+ => X+ X-
	   2 X- => Y+ Y-
	   3 Y- => X- X+ */	
	int corner_points[4][3]; // direction => codel
	// INIT_CORNER_POINTS(corner_points, y, x);
	fill_corner_points(y, x, height, width, corner_points);

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			if (map[y][x] == codel_index) 
				compare_points(y, x, corner_points);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			codel->corner_points[i][j] = corner_points[i][j];
}


void find_neighbor_codels(int height, int width, int map[][width], struct codel *codel_array[])
{  

	int current_codel_index = 0; 

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			int current_map_value = map[y][x];
			bool is_not_black_or_white = current_map_value != WHITE_INDEX && current_map_value != BLACK_INDEX;
			if (is_not_black_or_white && current_codel_index < current_map_value)
			{
				current_codel_index = map[y][x];
				resolve_codel(height, width, y, x, map, codel_array[current_codel_index], current_codel_index);
			}
		}

}
