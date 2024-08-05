#include <stdio.h>


void printarr_1(int *arr)
{
	printf("[%d, ", *arr);
	while( *(++arr) != '\0')
	{
		printf("%d, ", *arr);
	}
	printf("]\n");
}

void printarr_1_hex(int *arr)
{
	printf("[%x, ", *arr);
	while( *(++arr) != '\0')
	{
		printf("%x, ", *arr);
	}
	printf("]\n");
}

void prettify_hex (int value, char * outp)
{
	int digit;
	int temp_val = value;

	while (temp_val)
	{
		digit++;
		temp_val /= 16;
	}

	char value_char_arr[digit];
	
	for (int i = 0, temp_val = value; i < digit; i++)
	{
		value_char_arr[i] = value - (digit - i) * 16; 
	}

	char *optr = outp;
	*outp = 0;
	while (++*optr != '\0') *optr = 0;

	int digit_diff = 8 - digit;
	for (int i = 0; i < digit; i++)
	{
		optr[digit_diff + i - 1] = value_char_arr[i];
	}
}

/* WARNING: DOES NOT WORK */
void printarr_1_hex_pretty(int *arr)
{
	char number_text[8];

	
	putchar('[');
	while( *(++arr) != '\0')
	{

		prettify_hex(*arr, number_text);

		for (char *i = number_text; *i != '\0'; i++)
		{
			printf("%x", *i);

		}
		printf(", ");

	}

}
