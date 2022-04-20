#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "htab_private.h"
#include "io.h"

// according to resources I was searching for on the internet,
// the average number of unique words in a text is mostly in range
// of 5000-15000 words
// another advice I found was to use a number so the capacity of hash 
// table would be filled up to 70-75% and that this number should be a prime number
#define HTAB_SIZE 19609

#define WORD_MAX_SIZE 127

void print_pair(htab_pair_t *pair)
{
	printf("%s\t%d\n", pair->key, pair->value);
}


int main(int argc, char *argv[]) {
	FILE * fp = stdin;
	bool file_f = false;

	if (argc == 2) {
		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			fprintf(stderr, "ERROR: opening the file %s has failed.\n", argv[1]);
			exit(1);
		}

		file_f = true;
	} else if (argc > 2) {
		fprintf(stderr, "ERROR: Too many arguments\n");
		exit(1);
	}

	htab_t *t = htab_init(HTAB_SIZE);
	if (t == NULL) {
		fprintf(stderr, "ERROR: Initialization of hash table has failed.\n");
		exit(1);
	}

	htab_pair_t * pair = NULL;
	bool overflow_f = false;

	char word[WORD_MAX_SIZE];
	int word_length = 0;

	while((word_length = read_word(word, WORD_MAX_SIZE, fp)) != EOF) {
		if (word_length > WORD_MAX_SIZE && overflow_f == false) {
			fprintf(stderr, "WARNING: word is too long.\n");
			overflow_f = true;
		}

		pair = htab_lookup_add(t, word);
		if (pair == NULL) {
			fprintf(stderr, "ERROR: htab_lookup_add has failed.\n");
			htab_free(t);
			exit(1);
		}
		pair->value++;
	}

	htab_for_each(t, print_pair);

	htab_free(t);
	if (file_f) {
		fclose(fp);
	}

	exit(0);
}
