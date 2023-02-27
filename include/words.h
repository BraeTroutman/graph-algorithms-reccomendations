#ifndef WORDS_H
#define WORDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// read num_lines from a file and store them in lines after trimming whitespace
void readlines(const char *filename, char **lines, size_t num_lines);
// trim trailing whitespace
void rtrim(char *str);

#endif
