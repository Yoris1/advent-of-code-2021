#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAP_WIDTH 1000
#define MAP_HEIGHT 1000
#define input_buffer_length 128


void draw_line_on_array(char map[MAP_WIDTH][MAP_HEIGHT], int x1, int y1, int x2, int y2) {
	if(y1 == y2) {
		for(int x = x1; x <= x2; x++) {
			printf("drawing on! %i:%i\n", x, y1);
			map[x][y1] += 1;
		}
	}
	if(x1 == x2) {
		for(int y = y1; y<=y2; y++) {
			map[x1][y] += 1;
		}
	}
}
int count_overlaps(char map[MAP_WIDTH][MAP_HEIGHT]) {
	int count = 0;
	for(int x = 0; x < MAP_WIDTH; x++) {
		for(int y = 0 ; y< MAP_HEIGHT; y++) {
			if(map[x][y] > 1)
				count ++;
		}
	}
	return count;
}

void parse_line(char line[input_buffer_length], char map[MAP_WIDTH][MAP_HEIGHT]) {
	char* token = strchr(line, ',');
	int x1 = strtol(line, &token, 10);
	char* token2 = strchr(token, ','); 
	int y1 = strtol(token+1, &token2, 10);
	
	token = token2;
	token2 = strchr(token+3, ',');
	int x2 = strtol(token+3, &token2, 10); 
	token = token2;
	token2 = strchr(token+1, ',');
	int y2 = strtol(token+1, &token2, 10); 
	printf("X1: %i y1: %i; x2: %i y2: %i\n",x1, y1, x2, y2);

	draw_line_on_array(map, x1>x2?x2:x1, y1>y2?y2:y1, x1<x2?x2:x1, y1<y2?y2:y1);
}

int main() {
	FILE *input_file = fopen("input.inputfile", "r");
	char line[input_buffer_length] = {0};
	char map[MAP_WIDTH][MAP_HEIGHT] = {0};

	while(fgets(line, input_buffer_length, input_file))
		parse_line(line, map);
	printf("\nResult: %i\n", count_overlaps(map));
	return 0;
}