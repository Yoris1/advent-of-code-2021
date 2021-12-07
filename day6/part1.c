#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define INPUT_CHAR_ARRAY 50
void add_day(int8_t* fishies, size_t* fish_count) {
	size_t new_fish_count = 0;
	for(size_t x = 0; x < *fish_count; x++) {
		if(fishies[x] == 0) new_fish_count++;
	}
	fishies = realloc(fishies, *fish_count+new_fish_count);

	int new_fish_added = 0;

	for(size_t i = 0; i < *fish_count; i++) {
		int8_t fish = fishies[i];
		if(fish == 0) {
			fishies[i] = 7;
			fishies[*fish_count+(new_fish_added++)] = 8;
		}
		fishies[i] --;
	}
	*fish_count = *fish_count+new_fish_count;
}
void print_fishes(int8_t* fishies, size_t* fish_count) {
	for(size_t i = 0; i < *fish_count; i++) {
		printf("fish: %i\n", fishies[i]);
	}

}

int main() {
	FILE* input_file = fopen("input.inputfile", "r");	
	char converted_buffer[INPUT_CHAR_ARRAY];
	memset(converted_buffer, 15, INPUT_CHAR_ARRAY);
	
	size_t i = 0;
	char in = 0;
	while(in = fgetc(input_file)) {
		if(feof(input_file))
			break;
		if(in == ',')
			continue;
		in -= 0x30;
		printf("Read digit %i\n", in);
		converted_buffer[i++] = in;
	}

	fclose(input_file);

	printf("starting fish count: %i\n", i);

	int8_t* fishes = malloc(i*sizeof(int8_t));
	int y = 0;
	for(int x = 0 ; x < i; x++) {
		fishes[x] = converted_buffer[x];
	}
	print_fishes(fishes, &i);
	
	for(int j = 0; j < 18; j++) {
		add_day(fishes, &i);
		printf("Fishies after %i day count: %i\n",j+1, i);
		print_fishes(fishes, &i);
	}


	
	return 0;

}