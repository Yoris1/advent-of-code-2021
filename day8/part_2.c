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
int read_tokens(char tokens[10][8], char line[LINE_LENGTH]) {
	line = strtok(line, "|");
	char* token = strtok(line, " ");
	int i = 0;
	while(token != NULL) {
		memcpy(tokens[i++], token, strlen(token)+1);
		token = strtok(NULL, " ");
	}
}
void replace_tokens(int a, int b, char tokens[10][8]) {
	char extra_space[8] = {0};
	memcpy(extra_space, tokens[a], strlen(tokens[a])+1);
	memcpy(tokens[a], tokens[b], strlen(tokens[b])+1);
	memcpy(tokens[b], extra_space, strlen(extra_space)+1);
}
bool strstr_unordered(char* str, char* substr) {
	for(int i =0; i < strlen(substr); i++)
		if(strchr(str, substr[i]) == NULL)
			return false;
	return true;
}
bool already_sorted(char value[8], char sorted_tokens[10][8]) {
	for(int i = 0; i < 10; i++) {
		if(strcmp(sorted_tokens[i], value) == 0)
			return true;
	}
	return false;	
}
int get_token_value(char sorted_tokens[10][8], char token[8]) {
	for(int i = 0; i < 10; i++) {
		if(strlen(sorted_tokens[i]) == strlen(token)) {
			if(strstr_unordered(sorted_tokens[i], token))
				return i;
		}
	}
	return -1;
}
int get_number_from_line(char line[LINE_LENGTH]) {
	char* display_output = strchr(line, '|')+1;
	char* output = malloc((strlen(display_output)+1)*sizeof(char));
	memcpy(output, display_output, strlen(display_output)+1);

	char tokens[10][8] = {{0}};
	char sorted_tokens[10][8] = {{0}};
	read_tokens(tokens, line);

	// pass 1: sort the digits with a unique number of segments 
	for(int i = 0; i < 10; i++) {
		int token_length = strlen(tokens[i]);
		if(token_length == 2)
			memcpy(sorted_tokens[1], tokens[i], token_length+1);
		if(token_length == 3)
			memcpy(sorted_tokens[7], tokens[i], token_length+1);
		if(token_length == 4)
			memcpy(sorted_tokens[4], tokens[i], token_length+1);
		if(token_length == 7)
			memcpy(sorted_tokens[8], tokens[i], token_length+1);
	}

	for(int i = 0; i < 10; i++) {
		// pass 2: if a digit contains the same segments as 1 does and it's made of 5 segments it's 3; if it's made of 6 it's a 9 or 0
		// to differentiate between a 9 and a 0: if it has all the segments that a 4 does, it's a 9, otherwise it's a 0! 
		// if the digit does not contain the same segments as 1 and it's made of 6 letters it's a 6
		int token_length = strlen(tokens[i]);

		if(strstr_unordered(tokens[i], sorted_tokens[1])) {
			if(token_length == 5)
				memcpy(sorted_tokens[3], tokens[i], token_length+1);
			else if(token_length == 6) {
				if(strstr_unordered(tokens[i], sorted_tokens[4]))
					memcpy(sorted_tokens[9], tokens[i], token_length+1);
				else
					memcpy(sorted_tokens[0], tokens[i], token_length+1);
			}
		} else if(strlen(tokens[i]) == 6) {
			memcpy(sorted_tokens[6], tokens[i], token_length+1);
		}
	}

	for(int i = 0; i < 10; i++) {
		if(already_sorted(tokens[i], sorted_tokens)) continue;
		// pass 3: if a digit does not contain the same segments as 1 and it contains segments that a 9 doesn't have it's a 2, otherwise: 5
		int token_length = strlen(tokens[i]);
		if(!strstr_unordered(tokens[i], sorted_tokens[1])) {
			if(strstr_unordered(sorted_tokens[9], tokens[i]))
				memcpy(sorted_tokens[5], tokens[i], token_length+1);
			else
				memcpy(sorted_tokens[2], tokens[i], token_length+1);
		}
	}
	
	for(int i = 0; i < 10; i++) {
		int token_len = strlen(sorted_tokens[i]);
		if(token_len == 0) continue;
		printf("%s is %i(len: %i) | ", sorted_tokens[i], i, token_len);
	}
	printf("\n");

	printf("display output was: %s\n", output);
	char output_tokens[10][8]; // there are only 4, but i wanna use my read_tokens method
	read_tokens(output_tokens, output);
	int output_reading = 0;
	for(int i = 0; i < 4; i++) {
		int token_value = get_token_value(sorted_tokens, output_tokens[i]);
		output_reading *= 10;
		output_reading += token_value;
		printf("Token %i is %s val: %i; | ", i+1, output_tokens[i], token_value);
	}
	printf("\n");
	return output_reading;
}

int main() {
	char buffer[LINE_LENGTH];
	FILE* input_file = fopen("input.inputfile", "r");
	int result = 0;
	while(fgets(buffer, LINE_LENGTH, input_file) != NULL) {
		int newline_spot = strlen(buffer)-1; 
		if(buffer[newline_spot] == '\n')
			buffer[newline_spot] = 0;
		result += get_number_from_line(buffer);
	}
	printf("result is: %i\n", result);
}