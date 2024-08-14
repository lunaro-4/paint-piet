#include "headers.h"

struct color white_color = {0xff, 0xff, 0xff}, black_color = {0x0, 0x0, 0x0};

int get_chunk_value(FILE * fptr)
{
	int value = 0;
	for (char char_count = 0; char_count < 4; char_count++)
	{
		value += fgetc(fptr);
		// printf("%i", fgetc(fptr));
	}
	return value;
}


void print_color_matrix(int height, int widht, struct color *matrix[height][widht])
{
	for (int i = 0; i < height; i++) {
		printf("%d\t", i);
        for (int j = 0; j < widht  ; j++ ) {
            printf("R:%2x G:%2x B:%2x\t", matrix[i][j]->red, matrix[i][j]->green, matrix[i][j]->blue);
        }   
        printf("\n");
    }
}

void print_2d_int(int height, int width, int arr[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%i\t", arr[i][j]);
		}
		putchar('\n');
	}

}
void free_2d_colors(int height, int width, struct color *arr[][width])
{
	for (int i = 0; i < height; i++) {
        for (int j = 0; j < width  ; j++ ) {
			free(arr[i][j]);
		}
	}
}

bool is_light_hue(int color)
{
	return color >= 0xC0;
}

bool is_same_color(struct color *a, struct color *b)
{ 
	return (a->red == b->red && a->green == b->green && a->blue == b->blue );
}

bool is_same_color_fuzz(struct color *a, struct color *b)
{
	bool result = true;
	result = result && is_light_hue(a->red) == is_light_hue(b->red);
	result = result && is_light_hue(a->green) == is_light_hue(b->green);
	result = result && is_light_hue(a->blue) == is_light_hue(b->blue);
	return result;
}
bool is_black(struct color *col)
{
	return is_same_color(col, &black_color);
}
bool is_white(struct color *col)
{
	return is_same_color(col, &white_color);
}


void print_codel_array_corner_points(struct codel *codel_array[], int n_of_codels)
{
	for (int i = 2; i - 1 < n_of_codels; i++)
	{
		struct codel *cod = codel_array[i];
		int *corn_R = cod->corner_points[DP_RIGHT], *corn_D = cod->corner_points[DP_DOWN], *corn_L = cod->corner_points[DP_LEFT], *corn_U = cod->corner_points[DP_UP];
		printf("%2i\t Rx %2i Ryr %2i, Ryl %2i, Dy %2i Dxr %2i, Dxl %2i, Lx %2i Lry %2i, Lyl %2i, Uy %2i Uxr %2i, Uxl %2i, \n",
				i,
				corn_R[0], corn_R[1], corn_R[2],
				corn_D[0], corn_D[1], corn_D[2],
				corn_L[0], corn_L[1], corn_L[2],
				corn_U[0], corn_U[1], corn_U[2]
			  );

	}
}
void print_codel_array_colors(struct codel *codel_array[], int n_of_codels)
{
	for (int i = 2; i - 1 < n_of_codels; i++)
		printf("codel_index: %2i R: %2x, G: %2x, B: %2x\t", i, codel_array[i]->color.red, codel_array[i]->color.green, codel_array[i]->color.blue);
}
