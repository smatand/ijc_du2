#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "htab_private.h"
#include "io.h"

#define HTAB_SIZE 97
#define WORD_MAX_SIZE 127

void print_pair(htab_pair_t *pair)
{
	printf("%s: %d\n", pair->key, pair->value);
}


int main(int argc, char *argv[]) {
	FILE * fp = stdin;

	if (argc == 2) {
		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			fprintf(stderr, "ERROR: opening the file %s has failed.\n", argv[1]);
			return 1;
		}
	} else if (argc > 2) {
		fprintf(stderr, "ERROR: Too many arguments\n");
		return 1;
	}

	htab_t *t = htab_init(HTAB_SIZE);
	if (t == NULL) {
		fprintf(stderr, "ERROR: Initialization of hash table has failed.\n");
		return 1;
	}

	htab_pair_t * pair = NULL;
	bool overflow_f = false;
	//char word[WORD_MAX_SIZE];
	char * word = calloc(WORD_MAX_SIZE, 1);
	int word_length = 0;

	while((word_length = read_word(word, WORD_MAX_SIZE, fp)) != EOF) {
		if (word_length > WORD_MAX_SIZE && overflow_f == false) {
			fprintf(stderr, "WARNING: word is too long.\n");
			overflow_f = true;
		}

		pair = htab_lookup_add(t, word);
		if (pair == NULL) {
			fprintf(stderr, "ERROR: htab_lookup_add has failed.\n");
			return 1;
		}
		pair->value++;
	}

	htab_for_each(t, print_pair);

	htab_free(t);
	fclose(fp);

	return 0;
}
