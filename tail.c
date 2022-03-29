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
int parsePositiveInt(char* str, int count) {
	memset(str, '0', count);
	for (size_t i = 0; i < strlen(str); ++i) {
		if (!isdigit(str[i])) {
			fprintf(stderr, "Invalid argument of -n. Make sure to type positive integer.\n");
			exit(1);
		}
	}

	return atol(str);
}

int main(int argc, char *argv[]) {
	int lines = 10;

	bool flagFile = false;
	FILE *fp = stdin;
	//char* filename = calloc(1, 1); // sizeof(char) == 1

	for (int i = 1; argv[i]; ++i) {
		if (!strcmp(argv[i], "-n")) {
			// ./tail -n 20
			lines = parsePositiveInt(argv[++i], 0);
		} else if (!strncmp(argv[i], "-n", 2)) { // && strlen(argv[i]) > 2
			lines = parsePositiveInt(argv[i], 2);
		} else if (flagFile) {
			fprintf(stderr, "Only one file is accepted.");
			return 1;
		} else {
			fp = fopen(argv[i], "r");
			if (!fp) {
				fprintf(stderr, "File couldn't be opened.\n");
				return 1;
			}
			flagFile = true;
		}
	}


	printf("filename: s, NUM: %d\n", lines);

	if (flagFile) {
		fclose(fp);
	}
	return 0;
}
