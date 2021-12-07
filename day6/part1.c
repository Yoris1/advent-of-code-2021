#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define INPUT_CHAR_ARRAY 50

void print_fishies(int fishies[9]) {

	for(int i = 0; i < 9; i++) {
		printf("There are %i fishies whose internal timer is %i days\n", fishies[i], i);
	}
}

void add_day(int fishies[9]) {
	int new_fish = fishies[0];
	// todo replace all with 128bit + ints;
	fishies[0] = fishies[1];
	fishies[1] = fishies[2];
	fishies[2] = fishies[3];
	fishies[3] = fishies[4];
	fishies[4] = fishies[5];
	fishies[5] = fishies[6];
	fishies[6] = fishies[7]+new_fish;
	fishies[7] = fishies[8];
	fishies[8] = new_fish;
}
int sum_fishes(int fishies[9]) {
	int sum = 0;
	for(int i = 0; i < 9; i++) {
		sum += fishies[i];
	}
	return sum;
}

int main() {

	int fishies[9];
	memset(fishies, 0, sizeof(int)*9);
	FILE* input_file = fopen("input.inputfile", "r");	
	
	size_t i = 0;
	char in = 0;
	while(in = fgetc(input_file)) {
		if(feof(input_file))
			break;
		if(in == ',')
			continue;
		in -= 0x30;
		printf("Read digit %i\n", in);
		fishies[in] += 1;
	}

	fclose(input_file);

	for(int i = 0; i<80; i++)
		add_day(fishies);

	printf("there are %i fishes after 80 days\n", sum_fishes(fishies));
	return 0;

}