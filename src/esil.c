#include "../include/types.h"
#include "../include/esil.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//i64 find_index(char* const string, char delimiter, i64 length) {
//	for (i64 i=0; i<length && string[i] != delimiter; i++) {}
//	if (string[i] == delimiter) return i;
//	else return -1;
//}

char** tokens_from_string(char* string, i64 length, i64 *tokens_length) {
	i64 count = 1;
	for(i64 i=0; i<length; i++) {
		if (string[i] == ESIL_DELIMITER) count++;
	}

	char** tokens = calloc(count, sizeof(char*));

	i64 tokens_counter = 0;
	i64 from = 0;
	for (i64 i=0; i<length; i++) {
		if (string[i] == ESIL_DELIMITER) {
			string[i] = 0;
			if (i != 0) {
				if (string[i-1] != 0) {
					tokens[tokens_counter] = (string + from);
					tokens_counter++;
				}
			}
			from = i + 1;
		}
	}

	if (string[length - 1] != 0) {
		tokens[tokens_counter] = (string + from);
		tokens_counter++;
	}

	
	*tokens_length = tokens_counter;
	return tokens;
}

void free_tokens(char** tokens) {
	free(tokens);
}
