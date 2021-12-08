#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256

int count_unique_patterns_in_line(char line[LINE_LENGTH]) {
	int unique_digits = 0;

	char* output = strchr(line, '|')+1;
	char* token = strtok(output, " ");
	while(token != NULL) {
		int token_len = strlen(token);
		printf("%s:%i ", token, token_len);
		if(token_len == 2 || token_len == 3 || token_len == 4 || token_len == 7)
			unique_digits++;
		token = strtok(NULL, " ");
	}
	printf("\n");
	return unique_digits;
}

int main() {
	char buffer[LINE_LENGTH];
	FILE* input_file = fopen("input.inputfile", "r");
	int result = 0;
	while(fgets(buffer, LINE_LENGTH, input_file) != NULL) {
		int newline_spot = strlen(buffer)-1; 
		if(buffer[newline_spot] == '\n')
			buffer[newline_spot] = 0;
		result += count_unique_patterns_in_line(buffer);
	}
	printf("result is: %i\n", result);

}