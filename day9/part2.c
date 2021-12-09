#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_WIDTH 1000
#define INPUT_HEIGHT 1000


typedef struct vec2 {
	int x;
	int y;
} vec2;

void print_array(char heightmap[INPUT_HEIGHT][INPUT_WIDTH], vec2 dimensions) {
	for(int y = 0; y < dimensions.y; y++) {
		for(int x = 0; x < dimensions.x; x++) {
			printf("%c", heightmap[y][x]);
		}
		printf("\n");
	}
}
bool is_point_lowest_risk(char heightmap[INPUT_HEIGHT][INPUT_WIDTH], vec2 dimensions, vec2 pos) {
	for(int ox = -1; ox < 2; ox++) {
		for(int oy = -1; oy < 2; oy++) {
			if(ox != 0 && oy != 0) continue;
			if(ox == 0 && oy == 0) continue;
			vec2 adjusted_pos;
			adjusted_pos.x = ox+pos.x;
			adjusted_pos.y = oy+pos.y;
			if(adjusted_pos.x < 0 || adjusted_pos.x >= dimensions.x) continue;
			if(adjusted_pos.y < 0 || adjusted_pos.y >= dimensions.y) continue;
			//printf("Checking point %i:%i aka %i:%i\n", adjusted_x,adjusted_y,ox,oy);
			if(heightmap[pos.y][pos.x] >= heightmap[adjusted_pos.y][adjusted_pos.x]) return false;	
		}
	}
	return true;
}

bool can_point_reach_point(char heightmap[INPUT_HEIGHT][INPUT_WIDTH], vec2 dimensions, vec2 target_pos, vec2 pos) {
	if(pos.x == target_pos.x && pos.y == target_pos.y) return true;
	if(heightmap[pos.y][pos.x] == '9') return false;

	// some sort of algorithm to walk through all the x and y things and find if it has a connection with xy

	return false;
}
int get_basin_size(char heightmap[INPUT_HEIGHT][INPUT_WIDTH], vec2 dimensions, vec2 pos) {
	int basin_size = 0;
	for(int yy = 0; yy < dimensions.y; yy++) {
		for(int xx = 0; xx < dimensions.x; xx++) {
			vec2 current_pos = {xx, yy};
			if(can_point_reach_point(heightmap, dimensions, pos, current_pos)) {
				// does xxyy have connection to xy?
				basin_size++;
			}
		}
	}
	return basin_size;
}
int sum_lowest_risk_levels(char heightmap[INPUT_HEIGHT][INPUT_WIDTH], vec2 dimensions) {
	int sum = 0;
	//printf("Width is: %i Height is: %i\n", width, height);
	for (int y = 0; y < dimensions.y; y++) {
		for (int x = 0; x < dimensions.x; x++) {
			//printf("Checking point %i:%i: ", x, y);
			vec2 point = {x, y};
			if(is_point_lowest_risk(heightmap, dimensions, point))
				printf("The basin size is %i\n", get_basin_size(heightmap, dimensions, point));
			//printf("\n");
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

	vec2 dimensions = {width-1, line_count};
	print_array(heightmap, dimensions);
	printf("Result is: %i\n", sum_lowest_risk_levels(heightmap, dimensions));
}