#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Program that counts words and lines from stdinput
 *
 * Usage:
 * $ make && cat text_file.txt | outp.exe
 *
 */

int main(int argc, char *argv[])
{
	int character;
	int word, line;

	word = line = 0;

	while((character = getchar()) != EOF) {
		switch (character) {
			case '\t':
				;
			case ' ':
				++word;
				break;
			case '\n':
				++line;
				break;
				
		}
	}
	printf("Words: %i, lines: %i", word, line);
	
	
	

}
