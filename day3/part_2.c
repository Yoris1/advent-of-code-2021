#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define BUFF_COUNT 1001
#define BUFF_LENGTH 24

int get_most_common_bit(char buffer[BUFF_COUNT][BUFF_LENGTH], int entry_count, int digit, bool ignore[BUFF_COUNT]) {
	int zeros = 0, ones = 0;
	for(int i = 0; i < entry_count; i++) {
		if(ignore[i]) continue;
		ones += buffer[i][digit] == '1'?1:0;
		zeros += buffer[i][digit] == '0'?1:0;
	}
	if(ones == zeros) return 0;
	return ones>zeros?0:1;
}

int binary_string_to_int(char str[BUFF_LENGTH], int digits) {
	return (int)strtol(str, &str+strlen(str),2);
}

int get_rating(char buffer[BUFF_COUNT][BUFF_LENGTH], int entry_count, bool oxygen) {
	bool ignore[BUFF_COUNT] = {false};
	int digit_length = strlen(buffer[0])-1;

	for(int i = 0; i<digit_length; i++) {
		int common = get_most_common_bit(buffer, entry_count, i, ignore);
		
		if(oxygen) 
			common = !common;
		
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
					return binary_string_to_int(buffer[j], digit_length);
				}
			}
		}

	}


	return 0;
}

int main() {
	FILE *input = fopen("input.inputfile", "r");
	char file_buffer[BUFF_COUNT][BUFF_LENGTH];
	int i = 0;
	while (fgets(file_buffer[i++], 24, input)) continue;
	fclose(input);

	int o2  = get_rating(file_buffer, i, true);
	int co2 = get_rating(file_buffer, i, false);
	printf("CO2: %d, O2: %d, life support: %d\n", co2, o2, co2*o2);
}