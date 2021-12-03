#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define BUFF_COUNT 1000
#define BUFF_LENGTH 24

int get_most_common_bit(char buffer[BUFF_COUNT][BUFF_LENGTH], int entry_count, int digit, bool ignore[BUFF_COUNT]) {
	int zeroes = 0;
	int ones = 0;
	for(int i = 0; i < entry_count; i++) {
		if(ignore[i] == true) {
			continue;
		}
		if(buffer[i][digit] == '1')
			ones ++;
		else 
			zeroes++;
	}
	return ones>zeroes?1:0;
}

int get_rating(char buffer[BUFF_COUNT][BUFF_LENGTH], int entry_count, int digit_length) {
	bool ignore[BUFF_COUNT];
	for(int i = 0; i < BUFF_COUNT; i++) 
		ignore[i] = false;
	
	for(int i = 0; i<digit_length; i++) {
		int common = get_most_common_bit(buffer, entry_count, i, ignore);
		printf("Common: %d\n", common);
	}
	return 0;
}

int main() {
	FILE *input = fopen("input.inputfile", "r");

	int ones[24];
	int zeroes[24];
	for(int i = 0; i< 24; i++) {
		ones[i] = 0;
		zeroes[i] = 0;
	}


	char buffer[1000][24];
	int i = 0;
	while (true)
		if(fgets(buffer[i++], 23, input) == NULL) break; // reserving the first bit for ability to discard things
	fclose(input);

	int digit_length = strlen(buffer[0])-1;
	get_rating(buffer, i, digit_length);
}