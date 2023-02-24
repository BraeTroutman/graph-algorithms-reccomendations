#include "words.h"

void readlines(const char *filename, char **lines, size_t num_lines) {
	FILE *file = fopen(filename, "r");
	
	int i;
	for (i = 0; i < num_lines; i++) {
		lines[i] = calloc(32, sizeof(char));
		fgets(lines[i], 32, file);
		rtrim(lines[i]);
	}

	fclose(file);
}

void rtrim(char *str) {
	size_t length = strlen(str);

	int i;
	for (i = length - 1; isspace(str[i]); i--);
	str[i+1] = '\0';
}

