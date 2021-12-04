#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BOARDS 25
#define BINGO_DIMENSIONS 5

void parse_bingo_line(char line[BINGO_DIMENSIONS], char* input) {
	printf("Parsing %s", input);
	char* token = strtok(input, " ");
	int i = 0;
	do {
		line[i++] = atoi(token);
	}while(token = strtok(NULL, " "));
	printf("Parsed result: %i, %i, %i, %i, %i\n", line[0], line[1], line[2], line[3], line[4]);
}

int main() {
	FILE *input = fopen("input.inputfile", "r");
	int winning_numbers[256] = {-1};
	char line_buffer[124] = {'\0'};


	// parse winning numbers list
	fgets(line_buffer, 124, input);
	char* token;
	token = strtok(line_buffer, ",");
	int i = 0;
	do {
		if(token == NULL) break;
		char* end_pointer = token+strlen(token);
		int number = strtol(token, &end_pointer, 10);
		winning_numbers[i++] = number;
	} while((token = strtok(NULL, ",")));


	for(int j = 0; j<i; j++) {
		//printf("Num: %i\n", winning_numbers[j]);
	}



	char boards[MAX_BOARDS][BINGO_DIMENSIONS][BINGO_DIMENSIONS];

	int current_board = 0;
	int current_line = 0; 
	while(fgets(line_buffer, 124, input)) {
		if(!strcmp(line_buffer, "\n")) {
			current_board++;
			current_line= 0;
			printf("Next board:\n");
			continue;
		}
		parse_bingo_line(boards[current_board][current_line++], line_buffer);
		//printf("One line: %s", line_buffer);
	}
}