#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

#define LINE_LENGTH 512

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
 * @brief Read last n lines from file
 * 
 * @param fp file to read from
 * @param numOfLines number of lines to read
 */
void readTail(FILE * fp, unsigned long numOfLines) {
	char buffer[numOfLines][LINE_LENGTH]; // used as cyclical buffer
	char trash[LINE_LENGTH]; // for overflowed lines

	unsigned long index = 0;
	bool overflow_err_f = false;

	while (fgets(buffer[index % numOfLines], LINE_LENGTH, fp) != NULL) {
		if (strchr(buffer[index % numOfLines], '\n') == NULL) {
			// after overflow error, skip the rest of the lines
			do {
				fgets(trash, LINE_LENGTH, fp);
			} while (strchr(trash, '\n') == NULL);

			if (overflow_err_f == false) {
				fprintf(stderr, "ERROR: Detected line overflow\n");
				overflow_err_f = true;
			}
		}

		index++;
	}

	for (unsigned long i = 0; i < numOfLines; i++) {
		if (strchr(buffer[index % numOfLines], '\n') == NULL) {
			printf("%s\n", buffer[index % numOfLines]);
		} else {
			printf("%s", buffer[(index + i) % numOfLines]);
		}
	}
}

int main(int argc, char ** argv) {
	unsigned long lines = 10;

	bool file_f = false;
	FILE * fp = stdin;

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-n")) {
			lines = parsePositiveInt(argv[++i], 0);
		} else if (!strncmp(argv[i], "-n", 2)) {
			lines = parsePositiveInt(argv[i], 2);
		} else if (file_f) {
			fprintf(stderr, "Only one file is accepted.\n");
			return EXIT_FAILURE;
		} else {
			fp = fopen(argv[i], "r");
			if (!fp) {
				fprintf(stderr, "File couldn't be opened.\n");
				return EXIT_FAILURE;
			}
			file_f = true;
		}
	}

	readTail(fp, lines);

	if (file_f) {
		fclose(fp);
	}

	return EXIT_SUCCESS;
}
