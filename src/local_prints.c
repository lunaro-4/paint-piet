#include "project-headers.h"
#include <stdio.h>
#include <stdlib.h>


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

void print_int_array(int arr[], int arr_len)
{
	putchar('[');
	if (!arr_len)
	{
		int *ptr = arr;
		while (*ptr != '\0')
		{
			printf("%i, ", *ptr);
			ptr++;
		}
	}
	else 
		for (int i = 0; i < arr_len; i++)
			printf("%i, ", arr[i]);

	putchar(']');
	putchar('\n');
}
