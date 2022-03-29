#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define LINE_LENGTH 1024

/**
 * @brief Convert string to positive integer from specified position
 *
 * @param str string to convert from
 * @param count position from which to start converting
 *
 * @return -1 in case of error, otherwise parsed integer
 */
int parsePositiveInt(char* str, int count) {
	memset(str, '0', count);
	for (size_t i = 0; i < strlen(str); ++i) {
		if (!isdigit(str[i])) {
			fprintf(stderr, "Invalid argument of -n. Make sure to type positive integer.\n");
			exit(EXIT_FAILURE);
		}
	}

	return atol(str);
}

/**
 * @brief Count lines in file
 *
 * @param fp file to read from
 *
 * @return counted lines
 */
unsigned int countLines(FILE * fp) {
	char line[LINE_LENGTH];
	unsigned int count = 0;


	while (fgets(line, LINE_LENGTH, fp)) {
		count++;
	}

	rewind(fp);
	return count;
}

/**
 * @brief Print tail of file
 *
 * @param fp file to read from
 * @param numOfLines number of lines in fp
 * @param linesFromTail number of lines in tail of file to print
 */
void readLines(FILE * fp, unsigned int numOfLines, unsigned int linesFromTail) {
	char line[LINE_LENGTH];
	bool exceeded = false;

	while (fgets(line, LINE_LENGTH, fp)) {
		// skip the line which was creating by dividing previos line
		if (exceeded) {
			exceeded = false;
			continue;
		}

		--numOfLines; // reversed count

		if (!strchr(line, (int)'\n')) {
			fprintf(stderr, "Line exceeded the maximum length of characters in file %s.\n", __FILE__);
			exceeded = true;
			continue;
		}

		if (numOfLines < linesFromTail || numOfLines == 0) {
			printf("%s", line);
			--linesFromTail;
		}
	}

	rewind(fp);
}

int main(int argc, char *argv[]) {
	unsigned int lines = 10;

	bool flagFile = false;
	FILE * fp = stdin;

	for (int i = 1; argv[i]; ++i) {
		if (!strcmp(argv[i], "-n")) {
			// ./tail -n 20
			lines = parsePositiveInt(argv[++i], 0);
		} else if (!strncmp(argv[i], "-n", 2)) { // && strlen(argv[i]) > 2 (not needed?) TODO
			lines = parsePositiveInt(argv[i], 2);
		} else if (flagFile) {
			fprintf(stderr, "Only one file is accepted.");
			return EXIT_FAILURE;
		} else {
			fp = fopen(argv[i], "r");
			if (!fp) {
				fprintf(stderr, "File couldn't be opened.\n");
				return EXIT_FAILURE;
			}
			flagFile = true;
		}
	}

	readLines(fp, countLines(fp), lines);

	if (flagFile) {
		fclose(fp);
	}
	return EXIT_SUCCESS;
}
