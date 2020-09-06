#include <string.h>
#include "file.h"
#include "array.h"

char** split_string(char* str, char* delimiter) {
	char** segs = NULL;
	char* token = strtok(str, delimiter);
	while (token != NULL) {
		array_push(segs, token);
		token = strtok(NULL, " ");
	}
	return segs;
}
