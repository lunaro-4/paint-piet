#include <stdbool.h>
#include <stdio.h>


/* Count word length
 *
 * Usage:
 * Start by imputing number of words to process
 * Then input words, separated by  spaces
 *
 * The result is reversed histogram, showing the amount of characters in a word
 */

int main(int argc, char *argv[])
{
	int number_of_words;

	printf("Number of words to count length: %i\n", (number_of_words = getchar()-'0'));

	int word_lenght_array[number_of_words];

	for (int i = 0; i < number_of_words; i++){
		word_lenght_array[i] = 0;
	}

	int next_char = getchar();

	for (int word = 0; word < number_of_words ; word++) {
		next_char = getchar();
		putchar(next_char);
		while (true) {
			if (next_char == ' ' || next_char == '\n' || next_char == '\t') {
				break;
			}
			word_lenght_array[word]++;
			next_char = getchar();
		}
		printf("%i:%i\t", word, word_lenght_array[word]);
	}
	putchar('\n');

	bool need_more_rows = false;
	while (true) {
		for (int i = 0; i < number_of_words; ++i) {
			if (word_lenght_array[i] > 0) {
				printf("%s", "||");
				word_lenght_array[i]--;
				need_more_rows = true;
			}
			putchar('\t');
		}
		putchar('\n');

		if (!need_more_rows) {
			break;
		}
		need_more_rows = false;
	}
}
