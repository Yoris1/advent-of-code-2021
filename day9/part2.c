#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../aoc_libs/dynamic_array.h"

#define MAP_WIDTH 1000
#define MAP_HEIGHT 1000

typedef struct vec2 {
	int x;
	int y;
} vec2;


void print_array(char map[MAP_HEIGHT][MAP_WIDTH], vec2 dimensions) {
	for(int y = 0; y < dimensions.y; y++) {
		for(int x = 0; x < dimensions.x; x++) {
			printf("%c", map[y][x]);
		}
		printf("\n");
	}
}
bool is_point_lowest_risk(char map[MAP_HEIGHT][MAP_WIDTH], vec2 dimensions, vec2 pos) {
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
			if(map[pos.y][pos.x] >= map[adjusted_pos.y][adjusted_pos.x]) return false;	
		}
	}
	return true;
}
int compar(const void* a, const void* b) {
	vec2* a_ = a;
	vec2* b_ = b;
	if(b_->x == a_->x && a_->y == b_->y) return 0;
	return 1;
}
bool can_p1_reach_p2(char map[MAP_HEIGHT][MAP_WIDTH], vec2 dimensions, vec2 target_pos, vec2 pos, d_array *already_checked) {
	add_to_dynamic_array(already_checked, &pos);
	if(pos.x < 0 || pos.x >= dimensions.x || pos.y < 0 || pos.y >= dimensions.y) return false;
	if(pos.x == target_pos.x && pos.y == target_pos.y) return true;
	if(map[pos.y][pos.x] == '9') return false;

	printf("%i:%i vs %i:%i\n", pos.x, pos.y, target_pos.x, target_pos.y);

	for(int i = 1; i >= -1; i--) {
		if(i == 0) continue;
		vec2 p2 = {pos.x + i, pos.y};
		if(bsearch(&p2, already_checked->raw, already_checked->count, sizeof(vec2), compar) == NULL) {
			can_p1_reach_p2(map, dimensions, target_pos, p2, already_checked);
		}
	}
	printf("Done!\n");
	return false;
}

int get_basin_size(char map[MAP_HEIGHT][MAP_WIDTH], vec2 dimensions, vec2 p) {
	d_array ignored_points = create_dynamic_array(2, sizeof(vec2));

	int basin_size = 0;
	for(int y = 0; y < dimensions.y; y++) {
		for(int x = 0; x < dimensions.x; x++) {
			vec2 p2 = {x, y};
			if(can_p1_reach_p2(map, dimensions, p, p2, &ignored_points))
				basin_size ++;
		}
	}

	delete_dynamic_array(&ignored_points);
	return basin_size;
}

int do_basins(char map[MAP_HEIGHT][MAP_WIDTH], vec2 dimensions) {

	for(int y = 0; y < dimensions.y; y++) {
		for(int x = 0; x < dimensions.x; x++) {
			vec2 p = {x,y};
			if(is_point_lowest_risk(map, dimensions, p))
				printf("Basin size: %i\n", get_basin_size(map, dimensions, p));
		}
	}
	return 0;
}

int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE* input_file = fopen("input.inputfile", "r");
	int height = -1;
	char map[MAP_HEIGHT][MAP_WIDTH] = {0};
	while(fgets(map[++height], MAP_WIDTH, input_file));

	int width = strlen(map[0])-1;
	for(int y = 0; y < height; y++)
		map[y][width] = 0; // remove newlines
	
	int result = do_basins(map, (vec2){width, height});
	printf("Result is: %i\n", result);
}