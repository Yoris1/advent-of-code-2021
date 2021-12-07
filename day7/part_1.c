#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define POSITION_BUFFER_LENGTH 1000
#define FILE_READ_BUFFER 20

void get_max_crab_position(int positions[POSITION_BUFFER_LENGTH], int position_count, int* min, int* max) {
	*max = 0;
	*min = __INT_MAX__;
	for(int i = 0; i < position_count; i++) {
		if(positions[i] > *max) *max = positions[i];
		if(*min > positions[i]) *min = positions[i]; 
	}
}
int count_move_fuel(int positions[POSITION_BUFFER_LENGTH], int position_count, int target_pos) {
	int fuel_consumption = 0;
	for(int i = 0; i < position_count; i++) {
		fuel_consumption += abs(positions[i] - target_pos);
	}
	return fuel_consumption;
}


int main() {
	int positions[POSITION_BUFFER_LENGTH] = {0};
	int pos_count = 0;

	FILE* input_file = fopen("input.inputfile", "r");

	int i = 0;
	char line_in[FILE_READ_BUFFER] = {0}, c;
	while( true ) {
		c = fgetc(input_file);
		if(c == ',' || c == EOF){
			line_in[i] = '\0';
			int val = atoi(line_in);
			positions[pos_count++] = val;
			printf("%s : %i\n", line_in, val);
			i = 0;
			if(c == EOF) break;
			continue;
		}
 		line_in[i++] = c;
	}
	printf("there are a total of %i crabs\n", pos_count);

	int least_fuel = __INT_MAX__;
	int max,min;
	get_max_crab_position(positions, pos_count, &min, &max);
	for(int i = min; i <= max; i++) {
		int fuel = count_move_fuel(positions, pos_count, i);
		if(fuel < least_fuel) least_fuel = fuel;
		printf("Moving to %i would use %i fuel\n", i, fuel);
	}
	printf("The most efficient route would use %i fuel\n", least_fuel);
	return 0;
}