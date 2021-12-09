#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define INPUT_WIDTH 1000
#define INPUT_HEIGHT 1000
void print_array(char heightmap[INPUT_HEIGHT][INPUT_WIDTH], int width, int height) {
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			printf("%c", heightmap[y][x]);
		}
		printf("\n");
	}
}
bool is_point_lowest_risk(char heightmap[INPUT_HEIGHT][INPUT_WIDTH], int width, int height, int x, int y) {
	for(int ox = -1; ox < 2; ox++) {
		for(int oy = -1; oy < 2; oy++) {
			if(ox != 0 && oy != 0) continue;
			if(ox == 0 && oy == 0) continue;
			int adjusted_x, adjusted_y;
			adjusted_x = ox+x;
			adjusted_y = oy+y;
			if(adjusted_x < 0 || adjusted_x >= width) continue;
			if(adjusted_y < 0 || adjusted_y >= height) continue;
			//printf("Checking point %i:%i aka %i:%i\n", adjusted_x,adjusted_y,ox,oy);
			if(heightmap[y][x] >= heightmap[adjusted_y][adjusted_x]) return false;	
		}
	}
	return true;
}
int sum_lowest_risk_levels(char heightmap[INPUT_HEIGHT][INPUT_WIDTH], int width, int height) {
	int sum = 0;
	printf("Width is: %i Height is: %i\n", width, height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			printf("Checking point %i:%i: ", x, y);
			if(is_point_lowest_risk(heightmap, width, height, x, y)) {
				printf("Is lowest!");
				sum += heightmap[y][x]-0x30+1;
			}
			printf("\n");
		}
	}
	return sum;
}
int main(){
	FILE* input_file = fopen("input.inputfile", "r");
	int line_count = 0;
	char heightmap[INPUT_HEIGHT][INPUT_WIDTH];
	while(fgets(heightmap[line_count++], INPUT_WIDTH, input_file)) continue;
	line_count--;
	int width = strlen(heightmap[0]);
	for(int y = 0; y < line_count; y++) heightmap[y][width-1] = 0; // remove newlines

	print_array(heightmap, width,line_count);
	printf("Result is: %i\n", sum_lowest_risk_levels(heightmap, width-1, line_count));
}