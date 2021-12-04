#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BOARDS 200
#define BINGO_DIMENSIONS 5

void parse_bingo_line(char line[BINGO_DIMENSIONS], char* input) {
	//printf("Parsing %s", input);
	char* token = strtok(input, " ");
	int i = 0;
	do {
		line[i++] = atoi(token);
	}while(token = strtok(NULL, " "));
	//printf("Parsed result: %i, %i, %i, %i, %i\n", line[0], line[1], line[2], line[3], line[4]);
}
void mark_boards(char boards[MAX_BOARDS][BINGO_DIMENSIONS][BINGO_DIMENSIONS], int board_count, bool markers[MAX_BOARDS][BINGO_DIMENSIONS][BINGO_DIMENSIONS], int winning) {
	for(int j = 0; j < board_count; j++) {
		for(int k = 0; k<5; k++) {
			for(int t = 0; t < 5; t++) {
				if(boards[j][k][t] == winning)
					markers[j][k][t] = true;
			}
		}
	}
}

bool check_board_victory(bool markers[BINGO_DIMENSIONS][BINGO_DIMENSIONS], int board_count) {
	for(int i = 0; i < BINGO_DIMENSIONS; i++) {
		bool win = true;
		bool vertical = true;
		for(int x = 0; x<BINGO_DIMENSIONS; x++) {
			win &= markers[i][x];
			vertical &= markers[x][i];
		}
		if(win || vertical) {
			return true;
		}
	}
	return false;
}

int get_winning_board(bool markers[MAX_BOARDS][BINGO_DIMENSIONS][BINGO_DIMENSIONS], int board_count) {
	for(int t = 0; t < board_count; t++) {
		if(check_board_victory(markers[t], board_count)) {
			return t;
		}
	}
	return -1;
}

int get_board_unmarked_sum(char board[BINGO_DIMENSIONS][BINGO_DIMENSIONS], bool markers[BINGO_DIMENSIONS][BINGO_DIMENSIONS]) {
		int sum = 0;
		for(int x = 0; x<BINGO_DIMENSIONS; x++) {
			for(int y = 0; y<BINGO_DIMENSIONS; y++) {
				if(markers[x][y])
					continue;
				sum += board[x][y];
			}
		}
		return sum;
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

	int current_board = -1;
	int current_line = 0; 
	while(fgets(line_buffer, 124, input)) {
		if(!strcmp(line_buffer, "\n")) {
			current_board++;
			current_line= 0;
			//printf("Next board:\n");
			continue;
		}
		parse_bingo_line(boards[current_board][current_line++], line_buffer);
		//printf("One line: %s", line_buffer);
	}

	bool markers[MAX_BOARDS][BINGO_DIMENSIONS][BINGO_DIMENSIONS] = {0};
	for(int j = 0; j<i; j++) {
		printf("drawing %i:\n", winning_numbers[j]);
		mark_boards(boards, current_board+1, markers, winning_numbers[j]);
		int winning = get_winning_board(markers, current_board+1);
		if(winning != -1) {
			int result = get_board_unmarked_sum(boards[winning], markers[winning]);
			printf("Current winner: %i; %i; result: %i\n", winning_numbers[j], result, winning_numbers[j]* result);
			
			return 0;
		}
	}
	

}