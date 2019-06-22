#include <stdlib.h>
#include "read.h"

int lineCount(char* filename) {
	FILE *file;
	int lines = 0;
	char chr;
	file = fopen(filename, "r");

	if (file == NULL)
		exit(101);

	lines++;
	while (!feof(file)) {
		chr = fgetc(file);
		if (chr == '\n')
			lines++;
	}

	fclose(file);
	return lines;
}


char* readLine(char* filename, int nline) {
	int curLine;
	char* line = NULL;
	size_t len = 0;
	FILE* file;

	file = fopen(filename, "r");

	if (file == NULL)
		exit(101);

	for (curLine = 0; !feof(file) && curLine < nline; curLine++)
		getline(&line, &len, file);

	return line;
}
