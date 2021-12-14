#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include "../aoc_libs/dynamic_array.h"
#define BUFFER_SIZE 256

#define ANSI_ESCAPE_ERROR "\033[47m""\033[31m"
#define ANSI_ESCAPE_RESET "\x1b[0m"

uint64_t get_line_points(char line[BUFFER_SIZE]) {
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
				delete_dynamic_array(arr);
				return 0;
			}
		}
		else add_to_dynamic_array(arr, &closing_character);
	}
	((char*)arr->raw)[arr->count] = 0; // make string of completion characters null termianted

	printf(ANSI_ESCAPE_ERROR "%s" ANSI_ESCAPE_RESET " - Complete by adding " ANSI_ESCAPE_ERROR, line);

	uint64_t points = 0;
	for(int i = arr->count-1; i >=0 ; i--) {
		char c = ((char*)arr->raw)[i];
		printf("%c", c);
		points *= 5;
		points += strchr(closing_characters, c)-closing_characters+1;
	}
	printf(ANSI_ESCAPE_RESET" for "  ANSI_ESCAPE_ERROR"%ld" ANSI_ESCAPE_RESET " total points.\n", points);
	delete_dynamic_array(arr);
	return points;
}

int compare_ints(const void* a, const void* b) {
	const uint64_t *_a = a;
	const uint64_t *_b = b;
	return (int) (*_b>*_a);
}

int main() {
	FILE* input_file = fopen("day10/input.inputfile", "r");
	char line[BUFFER_SIZE];

	d_array* points = create_dynamic_array(1, sizeof(uint64_t));

	while(fgets(line, BUFFER_SIZE, input_file)) {
		if(line[strlen(line)-1] == '\n')
			line[strlen(line)-1] = 0; // remove newlines
		uint64_t line_points = get_line_points(line);
		if(line_points != 0)
			add_to_dynamic_array(points, &line_points);
	}

	qsort(points->raw, points->count, sizeof(uint64_t), compare_ints);
	printf("Result is %"PRIu64"\n", ((uint64_t*)points->raw)[points->count/2]);
	delete_dynamic_array(points);
	return 0;
}