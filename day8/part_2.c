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
		memcpy(tokens[i++], token, strlen(token));
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
void move_three_nine(char tokens[10][8], bool three) {
	for(int i = 0; i < 10; i++) {
		int token_len = strlen(tokens[i]);
		if(strstr_unordered(tokens[i], tokens[0])) {
			if(three && token_len == 5)
				replace_tokens(3, i, tokens);
			else if(!three && token_len == 6)
				replace_tokens(9, i, tokens);
		}
	}
}
void move_six(char tokens[10][8]) {
	for(int i = 0; i < 10; i++) {
		int token_len = strlen(tokens[i]);
		if(!strstr_unordered(tokens[i], tokens[0]) && token_len == 6	) {
			replace_tokens(i, 6, tokens);
		}
	}
}
void find_and_replace(char tokens[10][8], int length, int replace_with) {
	for(int i = 0; i < 10; i++) {
		if(strlen(tokens[i]) == length)
			replace_tokens(replace_with, i, tokens);
	}
}
void move_2_5(char tokens[10][8], bool two) {
	for(int i = 0; i< 10; i++) {
		if(!strstr_unordered(tokens[9], tokens[i])) { 
			if(two)
				replace_tokens(i, 2, tokens);
		} else if(two) {
			replace_tokens(i, 5, tokens);
		}
	}
}
int get_number_from_line(char line[LINE_LENGTH]) {
	char tokens[10][8] = {{0}};
	read_tokens(tokens, line);

	find_and_replace(tokens, 2, 1);
	find_and_replace(tokens, 4, 4);
	find_and_replace(tokens, 3, 7);
	find_and_replace(tokens, 7, 8);

	move_three_nine(tokens, false);
	move_three_nine(tokens, true);
	move_six(tokens);
	move_2_5(tokens, false);
	move_2_5(tokens, true);



	
	for(int i = 0; i < 10; i++) {
		int token_len = strlen(tokens[i]);
		printf("digit %i is %s (len: %i); ", i,  tokens[i], token_len);
	}
	printf("\n");
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