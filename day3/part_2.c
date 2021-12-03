#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define BUFF_COUNT 1001
#define BUFF_LENGTH 24

int get_most_common_bit(char buffer[BUFF_COUNT][BUFF_LENGTH], int entry_count, int digit, bool ignore[BUFF_COUNT], bool oxygen) {
	int zeroes = 0;
	int ones = 0;
	for(int i = 0; i < entry_count; i++) {
		if(ignore[i] == true) {
			continue;
		}
		if(buffer[i][digit] == '1')
			ones ++;
		else if(buffer[i][digit] == '0')
			zeroes++;
	}
	if(oxygen) {
		if(ones == zeroes) return 1;
		return ones>zeroes?1:0;
	}
	else {
		if(ones == zeroes) return 0;
		return ones>zeroes?0:1;
	}
}
int binary_string_to_int(char str[BUFF_LENGTH], int digits) {
	int result = 0;
	for(int i = 0; i< digits; i++) {
		if(str[i] == '1') {
			result += 1<<(digits-i-1);
		}
	}
	return result;
}
int get_rating(char buffer[BUFF_COUNT][BUFF_LENGTH], int entry_count, int digit_length, bool oxygen) {
	bool ignore[BUFF_COUNT];
	for(int i = 0; i < BUFF_COUNT; i++) 
		ignore[i] = false;
	
	for(int i = 0; i<digit_length; i++) {
		int common = get_most_common_bit(buffer, entry_count, i, ignore, oxygen);
		int kept = 0;
		for(int j = 0; j < entry_count; j++) {
			if(buffer[j][i] == common+0x30 && !ignore[j]) {
				//printf("Digit: %d(%d) Keeping: %s",i, common,  buffer[j]);
				kept++;
			} 
			else {
				ignore[j] = true;
			}
		}
		if(kept == 1) {
			for(int j = 0; j < entry_count; j++) {
				if(!ignore[j]) {

					//printf("Result: %s", buffer[j]);
					return binary_string_to_int(buffer[j], digit_length);
				}
			}
		}
	}
	return 0;
}

int main() {
	FILE *input = fopen("input.inputfile", "r");

	char buffer[BUFF_COUNT][BUFF_LENGTH];
	int i = 0;
	buffer[0][1] = 'T';
	while (true)
		if(fgets(buffer[i++], 24, input) == NULL) break; // reserving the first bit for ability to discard things
	fclose(input);

	int digit_length = strlen(buffer[0])-1;

	int o2=get_rating(buffer, i, digit_length, true);
	int co2 = get_rating(buffer, i, digit_length, false);
	printf("CO2: %d, O2: %d, life support: %d\n", co2, o2, co2*o2);
}