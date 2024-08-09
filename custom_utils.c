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

bool is_same_color(struct color *a, struct color *b)
{ 
	return (a->red == b->red && a->green == b->green && a->blue == b->blue );
}
bool is_black(struct color *col)
{
	return is_same_color(col, &black_color);
}
bool is_white(struct color *col)
{
	return is_same_color(col, &white_color);
}
