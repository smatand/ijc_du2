#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * @brief Convert string to positive integer from specified position
 *
 * @param str string to convert from
 * @param count position from which to start converting
 *
 * @return -1 in case of error, otherwise parsed integer
 */
int parseInteger(char* str, int count) {
	memset(str, '0', count);
	for (size_t i = 0; i < strlen(str); ++i) {
		if (!isdigit(str[i])) {
			return -1;
		}
	}

	return atol(str);
}

bool fileRead(FILE * fp, int lines) {

	return false;
}

int main(int argc, char *argv[]) {
	bool flagCmd = false;
	int lines = 10;
	
	FILE *fp = stdin;
	char* filename = calloc(1, 1); // sizeof(char) == 1

	switch (argc) {
		// in case of no argument selected, the default is set (reading from stdin last 10 lines)
		// ./tail filename -> valid
		// ./tail -n20 -> valid
		case 2:
			if (!strncmp(argv[1], "-n", 2)) {
				if (strlen(argv[1]) == 2) {
					fprintf(stderr, "Command -n must have one positive number.\n"); 
					return 1;
				}
				lines = parseInteger(argv[1], 2);
			} else {
				filename = realloc(filename, sizeof(argv[1]));
				strcpy(filename, argv[1]);
			}
			break;
		// ./tail filename -n20 -> valid
		// ./tail -n 20 -> valid
		// ./tail filename -n -> invalid
		case 3:
			// iterate through args to find "-n" parameter
			for (int i = 1; i < argc; ++i) {
				// in case there is only argument "-n", parse next argument
				if (!strcmp(argv[i], "-n")) {
					lines = ((i + 1) < argc) ? parseInteger(argv[++i], 0) : -1;
				} // in case the argument contains "-n20", parse the integer "20"
				else if (!strncmp(argv[i], "-n", 2)) {
					lines = parseInteger(argv[i], 2);
				} // otherwise it must be a name of file
				else if (strlen(filename)) {
					fprintf(stderr, "Only one file is accepted.");
					return 1;
				} else {
					filename = realloc(filename, sizeof(argv[i]));
					strcpy(filename, argv[i]);
				}
			}
			break;
		// ./tail filename -n 20 -> valid
		// ./tail -n 20 filename -> valid
		// ./tail filename -n -> invalid
		// ./tail filename filename filename -> invalid
		// ./tail -n 20 -n21 -> valid
		case 4:
			for (int i = 1; i < argc; ++i) {
				if (!strcmp(argv[i], "-n")) {
					lines = ((i + 1) < argc) ? parseInteger(argv[++i], 0) : -1;
				} else if (!strncmp(argv[i], "-n", 2)) {
					lines = parseInteger(argv[i], 2);
				} else if (strlen(filename)) {
					fprintf(stderr, "Only one file is accepted.");
					return 1;
				} else {
					filename = realloc(filename, sizeof(argv[i]));
					strcpy(filename, argv[i]);
				}
			}
			break;
		default:
			fprintf(stderr, "Too many arguments.\nUsage: ./tail [-n NUMBER] [file]\n");
			return 1;
	}

	if (lines < 0) {
		fprintf(stderr, "Invalid argument of -n. Make sure to type positive integer.\n");
		return 1;
	}
	
	//printf("filename: %s, NUM: %d\n", filename, lines);

	free(filename);
	return 0;
}
