#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../aoc_libs/dynamic_array.h"
#define BUFFER_SIZE 256

#define ANSI_ESCAPE_ERROR "\033[47m""\033[31m"
#define ANSI_ESCAPE_RESET "\x1b[0m"

int get_line_points(char line[BUFFER_SIZE]) {
	const char closing_characters[] = ")]}>";
	const char character_pairs[] = "()[]{}<>";

	d_array *arr = create_dynamic_array(2,  sizeof(char));
	int length = strlen(line);

	for(int i = 0; i < length; i++) {
		char c = line[i];
		if(c == '\n') break;
		char closing_character = strchr(character_pairs, c)[1];

		if(strchr(closing_characters, c) != NULL) {
			char expected_char = ((char*)arr->raw)[--(arr->count)];
			if(expected_char != c) {
				printf(ANSI_ESCAPE_ERROR"`%s`"ANSI_ESCAPE_RESET "- expected "ANSI_ESCAPE_ERROR "`%c`" ANSI_ESCAPE_RESET ", but found "ANSI_ESCAPE_ERROR"`%c`" ANSI_ESCAPE_RESET"instead\n", line, expected_char, c);
				delete_dynamic_array(arr);
				if(c == ')') return 3;
				if(c == ']') return 57;
				if(c == '}') return 1197;
				if(c == '>') return 25137;
			}
		}
		else add_to_dynamic_array(arr, &closing_character);
	}
	delete_dynamic_array(arr);
	return 0;
}

int main() {
	FILE* input_file = fopen("input.inputfile", "r");
	char line[BUFFER_SIZE];

	int total_points = 0 ;

	while(fgets(line, BUFFER_SIZE, input_file)) {
		line[strlen(line)-1] = 0; // remove newlines
		total_points+=get_line_points(line);
	}

	printf("Total syntax error score for the errors: %i\n", total_points);
	return 0;
}