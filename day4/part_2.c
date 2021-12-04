#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BOARDS 200
#define BINGO_DIMENSIONS 5
#define FILEREAD_BUFFER_LENGTH 1024

void parse_bingo_line(char line[BINGO_DIMENSIONS], char* input) {
	char* token = strtok(input, " ");
	int i = 0;
	do line[i++] = atoi(token);
	while(token = strtok(NULL, " "));
}

void mark_boards(char boards[MAX_BOARDS][BINGO_DIMENSIONS][BINGO_DIMENSIONS], int board_count, bool markers[MAX_BOARDS][BINGO_DIMENSIONS][BINGO_DIMENSIONS], int draw) {
	for(int board = 0; board < board_count; board++)
		for(int x = 0; x<BINGO_DIMENSIONS; x++)
			for(int y = 0; y < BINGO_DIMENSIONS; y++)
				if(boards[board][x][y] == draw)
					markers[board][x][y] = true;

}

bool check_board_victory(bool markers[BINGO_DIMENSIONS][BINGO_DIMENSIONS], int board_count) {
	for(int y = 0; y < BINGO_DIMENSIONS; y++) {
		bool horizontal_win = true;
		bool vertical_win = true;
		for(int x = 0; x<BINGO_DIMENSIONS; x++) {
			horizontal_win &= markers[y][x];
			vertical_win &= markers[x][y];
		}

		if(horizontal_win || vertical_win)
			return true;
	}
	return false;
}

bool is_board_ignored(int ignored_boards[], int ignored_boards_count, int board) {
	for(int i = 0; i < ignored_boards_count; i++) {
		if(board == ignored_boards[i]) {
			return true;
		}
	}
	return false;
}

int get_winning_board(bool markers[MAX_BOARDS][BINGO_DIMENSIONS][BINGO_DIMENSIONS], int board_count, int ignored_boards[], int ignored_boards_count) {
	for(int board = 0; board < board_count; board++) {
		if(is_board_ignored(ignored_boards, ignored_boards_count, board))
			continue;
		if(check_board_victory(markers[board], board_count))
			return board;
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

int parse_winning_numbers(int winning_numbers[256], char* line) {
	// return value: the count of winning numbers
	char* token;
	token = strtok(line, ",");
	int i = 0;
	do {
		if(token == NULL) break;
		char* end_pointer = token+strlen(token);
		int number = strtol(token, &end_pointer, 10);
		winning_numbers[i++] = number;
	} while((token = strtok(NULL, ",")));
	return i;
}

int main() {
	FILE *input = fopen("input.inputfile", "r");

	char line_buffer[FILEREAD_BUFFER_LENGTH] = {'\0'};
	fgets(line_buffer, FILEREAD_BUFFER_LENGTH, input);


	int winning_numbers[256] = {-1};
	int winning_number_count = parse_winning_numbers(winning_numbers, line_buffer);


	char boards[MAX_BOARDS][BINGO_DIMENSIONS][BINGO_DIMENSIONS];

	int current_board = -1;
	int current_line = 0; 

	while(fgets(line_buffer, FILEREAD_BUFFER_LENGTH, input)) {
		if(!strcmp(line_buffer, "\n")) {
			current_board++;
			current_line= 0;
			continue;
		}
		parse_bingo_line(boards[current_board][current_line++], line_buffer);
	}

	int board_count = current_board+1;

	int ignored_boards[255] = {-1};
	int ignored_boards_count = 0;
	bool markers[MAX_BOARDS][BINGO_DIMENSIONS][BINGO_DIMENSIONS] = {0};

	printf("There will be %i draws", winning_number_count);

	for(int j = 0; j<winning_number_count; j++) {

		printf("drawing %i:\n", winning_numbers[j]);
		mark_boards(boards, board_count, markers, winning_numbers[j]);


		int winning = -1;
		winning = get_winning_board(markers, board_count, ignored_boards, ignored_boards_count);

		while(winning != -1) {
			int result = get_board_unmarked_sum(boards[winning], markers[winning]);
			ignored_boards[ignored_boards_count++] = winning;

			printf("Current winner(%i): %i; %i; result: %i\n",winning, winning_numbers[j], result, winning_numbers[j]* result);
			printf("ignored boards: %i", ignored_boards_count);
			winning = get_winning_board(markers, board_count, ignored_boards, ignored_boards_count);
		}

	}

}