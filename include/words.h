#ifndef WORDS_H
#define WORDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void readlines(const char *filename, char **lines, size_t num_lines);
void rtrim(char *str);

#endif
