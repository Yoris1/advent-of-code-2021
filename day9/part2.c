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


void print_array(char map[MAP_HEIGHT][MAP_WIDTH], vec2 map_bounds) {
	for(int y = 0; y < map_bounds.y; y++) {
		for(int x = 0; x < map_bounds.x; x++) {
			printf("%c", map[y][x]);
		}
		printf("\n");
	}
}
bool point_in_bounds(vec2 p, vec2 bounds) {
	if(p.x < 0 || p.x >= bounds.x) return false;
	if(p.y < 0 || p.y >= bounds.y) return false;
	return true;
}

bool is_point_lowest_risk(char map[MAP_HEIGHT][MAP_WIDTH], vec2 map_bounds, vec2 pos) {
	for(int ox = -1; ox < 2; ox++) {
		for(int oy = -1; oy < 2; oy++) {
			if(ox != 0 && oy != 0) continue;
			if(ox == 0 && oy == 0) continue;
			vec2 adjusted_pos;
			adjusted_pos.x = ox+pos.x;
			adjusted_pos.y = oy+pos.y;
			if(!point_in_bounds(adjusted_pos, map_bounds)) continue;
			//printf("Checking point %i:%i aka %i:%i\n", adjusted_x,adjusted_y,ox,oy);
			if(map[pos.y][pos.x] >= map[adjusted_pos.y][adjusted_pos.x]) return false;	
		}
	}
	return true;
}
int compare_vec2(const void* a, const void* b) {
	const vec2 *a_ = a, *b_ = b;
	if(b_->x == a_->x && a_->y == b_->y) return 0;
	return 1;
}
void print_points_in_array(d_array *arr) {
	printf("Points in the dynmaic point array: ");
	vec2* raw = arr->raw;
	for(int i = 0; i < arr->count; i++) {
		printf("%i:%i, ", raw[i].x, raw[i].y);
	}
	printf("\n");
}
bool vec_in_array(d_array *arr, vec2 p) {
	vec2* raw = arr->raw;
	for(int i = 0; i < arr->count; i++) {
		if(raw[i].x == p.x && raw[i].y == p.y) return true;
	}
	return false;
}
int count_points_p_can_reach(char map[MAP_HEIGHT][MAP_WIDTH], vec2 map_bounds, vec2 p, d_array *counted_points) {
	for(int x = -1; x <= 1; x++) {
		for(int y = -1; y <= 1; y++) {
			if(x == 0 && y == 0) continue;
			if(x != 0 && y != 0) continue;
			vec2 p2 = {p.x+x, p.y+y};
			if(!point_in_bounds(p2, map_bounds)) continue;
			if(map[p2.y][p2.x] == '9') continue;
			if(vec_in_array(counted_points, p2)) {
				printf("Point %i:%i is already counted! \n", p2.x, p2.y); // is it ignoring first value?
				continue;
			}
			add_to_dynamic_array(counted_points, &p2);
			print_points_in_array(counted_points);
			printf("%i:%i is fine, value: %c\n", p2.x, p2.y, map[p2.y][p2.x]);
			count_points_p_can_reach(map, map_bounds, p2, counted_points);
		}
	}

}

int get_basin_size(char map[MAP_HEIGHT][MAP_WIDTH], vec2 map_bounds, vec2 p) {
	d_array counted_points = create_dynamic_array(20, sizeof(vec2));
	count_points_p_can_reach(map, map_bounds, p, &counted_points);
	int basin_size = counted_points.count;

	delete_dynamic_array(&counted_points);

	return basin_size;
}

int do_basins(char map[MAP_HEIGHT][MAP_WIDTH], vec2 map_bounds) {
	for(int y = 0; y < map_bounds.y; y++) {
		for(int x = 0; x < map_bounds.x; x++) {
			vec2 p = {x,y};
			if(is_point_lowest_risk(map, map_bounds, p)) {
				printf("Basin size is: %i\n", get_basin_size(map, map_bounds, p));
			}
		}
	}
	return 0;
}

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE* input_file = fopen("input.inputfile", "r");
	int height = -1;
	char map[MAP_HEIGHT][MAP_WIDTH] = {0};
	while(fgets(map[++height], MAP_WIDTH, input_file));

	int width = strlen(map[0])-1;
	for(int y = 0; y < height; y++)
		map[y][width] = 0; // remove newlines
	print_array(map, (vec2){width, height});
	int result = do_basins(map, (vec2){width, height});
	printf("Part 2 result is: %i\n", result);
	return 0;
}