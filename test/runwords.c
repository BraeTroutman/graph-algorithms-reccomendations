#include "words.h"

int main() {
	char **lines = calloc(1024, sizeof(char*));
	readlines("data/words.txt", lines, 1024);

	int i;
	for (i = 0; i < 1024; i++) puts(lines[i]);
}

