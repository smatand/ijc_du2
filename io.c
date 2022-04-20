// io.c
// Riesenie IJC-DU2, priklad b), 20.4.2022
// Author: Andrej Smatana, FIT
// Prelozene: gcc 9.4.0
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "io.h"

int read_word(char *s, int max, FILE *f) {
	if (f == NULL) {
		return -1;
	}

	int c = 0;
	int length = 0;

	// skip leading whitespace
	while ((c = fgetc(f)) != EOF && isspace(c))
		;

	if (c == EOF) {
		return EOF;
	}

	s[0] = (char)c;
	length++;

	for (c = fgetc(f); c != EOF && !isspace(c) && length < max-1; c = fgetc(f), length++) {
		s[length] = (char)c;
	}

	// append null terminator
	s[length] = '\0';

	if (length == max-1) {
		while (isspace(c = fgetc(f))) {
			length++;
		}
	}

	return length;
}

