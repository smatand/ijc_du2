#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

#define LINE_LENGTH 513 // 512 + 1 for the '\n' char

/**
 * @brief Convert string to positive integer from specified position
 *
 * @param str string to convert from
 * @param count position from which to start converting
 *
 * @return parsed integer
 */
unsigned long parsePositiveInt(char* str, const int count) {
	memset(str, '0', count); // set 1st count chars to 0
	for (size_t i = 0; i < strlen(str); ++i) {
		if (!isdigit(str[i])) {
			fprintf(stderr, "Invalid argument of -n. Make sure to type positive integer.\n");
			exit(EXIT_FAILURE);
		}
	}

	const unsigned long lines = strtoul(str, NULL, 10);

	if (errno) {
		fprintf(stderr, "Range error of parsed number occured.\n");
		exit(EXIT_FAILURE);
	}

	return lines;
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

	// count lines with newline character
	while (fgets(line, LINE_LENGTH, fp)) {
		if (strchr(line, '\n') != NULL) {
			++count;
		}
	}

	rewind(fp);
	return count;
}

/**
 * @brief Print tail of file
 *
 * @param fp file to read from
 * @param linesFromTail number of lines in tail of file to print
 */
void readLines(FILE * fp, unsigned long linesFromTail) {
	char line[LINE_LENGTH];
	unsigned long numOfLines = countLines(fp);


	while (fgets(line, LINE_LENGTH+1, fp)) {
		// move the position to the first line of tail
		if (numOfLines > linesFromTail) {
			if (strchr(line, '\n') != NULL) {
				numOfLines--;
			}
		} else if (strchr(line, '\n') != NULL) {
			printf("%s", line);
		} else {
			fprintf(stderr, "ERROR: Detected line overflow\n");
			// move the position to the next line
			while(fgetc(fp) != '\n')
				;
		}
	}
	rewind(fp);
}

int main(int argc, char *argv[]) {
	unsigned long lines = 10;

	bool flagFile = false;
	FILE * fp = stdin;

	for (int i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-n")) {
			lines = parsePositiveInt(argv[++i], 0);
		} else if (!strncmp(argv[i], "-n", 2)) {
			lines = parsePositiveInt(argv[i], 2);
		} else if (flagFile) {
			fprintf(stderr, "Only one file is accepted.\n");
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

	readLines(fp, lines);

	if (flagFile) {
		fclose(fp);
	}

	return EXIT_SUCCESS;
}
