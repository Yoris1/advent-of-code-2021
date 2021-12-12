#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../aoc_libs/dynamic_array.h"

#define MAP_WIDTH 1000
#define MAP_HEIGHT 1000

typedef struct vec2i {
	int x;
	int y;
} vec2i;

void print_array(char map[MAP_HEIGHT][MAP_WIDTH], vec2i map_bounds) {
	for(int y = 0; y < map_bounds.y; y++) {
		for(int x = 0; x < map_bounds.x; x++)
			printf("%c", map[y][x]);
		printf("\n");
	}
}

bool point_in_bounds(vec2i p, vec2i bounds) {
	if(p.x < 0 || p.x >= bounds.x) return false;
	if(p.y < 0 || p.y >= bounds.y) return false;
	return true;
}

bool is_point_lowest_risk(char map[MAP_HEIGHT][MAP_WIDTH], vec2i map_bounds, vec2i pos) {
	for(int ox = -1; ox < 2; ox++) {
		for(int oy = -1; oy < 2; oy++) {
			if(ox != 0 && oy != 0) continue;
			if(ox == 0 && oy == 0) continue;
			vec2i adjusted_pos;
			adjusted_pos.x = ox+pos.x;
			adjusted_pos.y = oy+pos.y;
			if(!point_in_bounds(adjusted_pos, map_bounds)) continue;
			if(map[pos.y][pos.x] >= map[adjusted_pos.y][adjusted_pos.x]) return false;	
		}
	}
	return true;
}

bool vec2i_in_dynamic_array(d_array *arr, vec2i p) {
	vec2i* raw = arr->raw;
	for(int i = 0; i < arr->count; i++)
		if(raw[i].x == p.x && raw[i].y == p.y) return true;
	return false;
}
int compare_ints(const void* a, const void*b) {
	return (*(int*)b)-(*(int*)a);
}
int count_points_p_can_reach(char map[MAP_HEIGHT][MAP_WIDTH], vec2i map_bounds, vec2i p, d_array *counted_points) {
	bool root = false;
	if(counted_points == NULL)  {
		root = true;
		counted_points = create_dynamic_array(5, sizeof(vec2i));
	}
	for(int x = -1; x <= 1; x++) {
		for(int y = -1; y <= 1; y++) {
			if(x == 0 && y == 0) continue;
			if(x != 0 && y != 0) continue;
			vec2i p2 = {p.x+x, p.y+y};
			if(!point_in_bounds(p2, map_bounds)) continue;
			if(map[p2.y][p2.x] == '9') continue;
			if(vec2i_in_dynamic_array(counted_points, p2)) continue;
			add_to_dynamic_array(counted_points, &p2);
			//printf("%i:%i is fine, value: %c\n", p2.x, p2.y, map[p2.y][p2.x]);
			count_points_p_can_reach(map, map_bounds, p2, counted_points);
		}
	}
	if(root) {
		int result = counted_points->count;
		delete_dynamic_array(counted_points);
		return result;
	}
	return -1;
}

int get_basin_sizes(char map[MAP_HEIGHT][MAP_WIDTH], vec2i map_bounds) {
	d_array* basin_sizes = create_dynamic_array(1, sizeof(int));
	for(int y = 0; y < map_bounds.y; y++) {
		for(int x = 0; x < map_bounds.x; x++) {
			vec2i p = {x,y};
			if(is_point_lowest_risk(map, map_bounds, p)) {
				int basin_size = count_points_p_can_reach(map, map_bounds, p, NULL);
				add_to_dynamic_array(basin_sizes, &basin_size);
				printf("Basin size is: %i\n", basin_size);
			}
		}
	}
	qsort(basin_sizes->raw, basin_sizes->count, sizeof(int), compare_ints);

	int result = 1;
	for(int i = 0; i < 3; i++)
		result *= ( (int*)basin_sizes->raw )[i];
	
	delete_dynamic_array(basin_sizes);
	return result;
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
	print_array(map, (vec2i){width, height});
	int result = get_basin_sizes(map, (vec2i){width, height});
	printf("Part 2 result is: %i\n", result);
	return 0;
}