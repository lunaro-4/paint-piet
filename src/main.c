#include "headers.h"
#include "png.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define compare_Rx(corner_point, x, replace_value) ((corner_point[0] < x) ?  replace_value : corner_point[1])
#define compare_Dy(corner_point, y, replace_value) ((corner_point < x) ?  replace_value : corner_point)
#define compare_Lx(corner_point, x, replace_value) ((corner_point < x) ?  replace_value : corner_point)
#define compare_Uy(corner_point, y, replace_value) ((corner_point < x) ?  replace_value : corner_point)


void resolve_codel (int height, int width, int y, int x, int map[][width], struct codel *codel, int codel_index)
{
	/* corner_points scheme:
	   0 X+ => Y- Y+
	   1 Y+ => X+ X-
	   2 X- => Y+ Y-
	   3 Y- => X- X+ */	
	int corner_points[4][3]; // direction => codel
	// INIT_CORNER_POINTS(corner_points, y, x);

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
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)

			if (map[y][x] == codel_index) 
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

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			codel->corner_points[i][j] = corner_points[i][j];
}

void find_neighbor_codels(int height, int width, int map[][width], struct codel *codel_array[])
{  

	int current_codel_index = 0; 

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int current_map_value = map[y][x];
			bool is_not_black_or_white = current_map_value != WHITE_INDEX && current_map_value != BLACK_INDEX;
			// printf("%i\t", is_not_black_or_white);
			if (is_not_black_or_white && current_map_value > current_codel_index)
			{
				current_codel_index = map[y][x];
				resolve_codel(height, width, y, x, map, codel_array[current_codel_index], current_codel_index);
			}
		}

	}
}




int main(int argc, char *argv[])
{
	struct codel cod;

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

	int height, width;
	get_height_and_width(fptr, &height, &width);

	fclose(fptr);
	fptr = fopen(file_path, "r");


	struct color *matrix[height][width];

	for (int i = 0; i < height; i++) {
        for (int j = 0; j < width  ; j++ ) {
			static struct color *c;
			c = malloc(sizeof(struct color));
			matrix[i][j] = c;
		}
	}

	create_matrix(fptr, width, height, matrix);
	// print_color_matrix(height, width, matrix);


	int map[height][width], n_of_codels;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			map[y][x] = -1;
		}
	}
	struct codel *codel_array[CODEL_ARRAY_SIZE];
	fill_2d_map(height, width, map, matrix, &n_of_codels, codel_array);


	// print_2d_int(height, width, map);
	// for (int i = 2; i < n_of_codels; i++)
	// 	printf("codel_index: %2i R: %2x, G: %2x, B: %2x\t", i, codel_array[i]->color.red, codel_array[i]->color.green, codel_array[i]->color.blue);
	// printf("\n%i\n", n_of_codels);
	
	find_neighbor_codels(height, width, map, codel_array);

	for (int i = 2; i < n_of_codels; i++)
	{
		struct codel *cod = codel_array[i];
		int *corn_R = cod->corner_points[0], *corn_D = cod->corner_points[1], *corn_L = cod->corner_points[2], *corn_U = cod->corner_points[3];
		/* printf("%2i\t Rx %2i Ryr %2i, Ryl %2i, Dy %2i Dxr %2i, Dxl %2i, Lx %2i Lry %2i, Lyl %2i, Uy %2i Uxr %2i, Uxl %2i, \n",
				i,
				corn_R[0], corn_R[1], corn_R[2],
				corn_D[0], corn_D[1], corn_D[2],
				corn_L[0], corn_L[1], corn_L[2],
				corn_U[0], corn_U[1], corn_U[2]
			  ); */

	}

	for (int i = 2; i < n_of_codels; i++)
		free(codel_array[i]);

	free_2d_colors(height, width, matrix);
	return 0;
}

