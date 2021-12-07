#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

#define SIMULATION_DAYS 256

void print_fishies(uint64_t fishies[9]) {
	for(int i = 0; i < 9; i++)
		printf("There are %i fishies whose internal timer is %i days\n", fishies[i], i);
}

void add_day(uint64_t fishies[9]) {
	uint64_t new_fish = fishies[0];
	for(int i = 0; i < 6; i++)
		fishies[i] = fishies[i+1];
	
	fishies[6] = fishies[7]+new_fish;
	fishies[7] = fishies[8];
	fishies[8] = new_fish;
}

uint64_t count_fish(uint64_t fishies[9]) {
	uint64_t sum = 0;
	for(int i = 0; i < 9; i++)
		sum += fishies[i];
	return sum;
}

int main() {
	uint64_t fishies[9] = {0};

	FILE* input_file = fopen("input.inputfile", "r");

	char in = 0;
	while(in = fgetc(input_file)) {
		if(feof(input_file))
			break;
		if(in == ',')
			continue;
		fishies[in-0x30] += 1;
	}
	fclose(input_file);

	for(int i = 0; i<SIMULATION_DAYS; i++)
		add_day(fishies);
	uint64_t total_fish=count_fish(fishies);

	if(total_fish>INT64_MAX)
		printf("overflow!\n");
	
	printf("there will be a total of %" PRIu64 " fish after %i days\n", total_fish, SIMULATION_DAYS);
	return 0;

}