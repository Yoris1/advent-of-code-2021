#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define BUFF_COUNT 1001
#define BUFF_LENGTH 24

int get_most_common_bit(const char buffer[BUFF_COUNT][BUFF_LENGTH], const bool* eliminated_entries, int entry_count, int digit) {
	int zeros = 0, ones = 0;
	for(int i = 0; i < entry_count; i++) {
		if(eliminated_entries[i]) continue;
		ones += buffer[i][digit] == '1'?1:0;
		zeros += buffer[i][digit] == '0'?1:0;
	}
	if(ones == zeros) return 0;
	return ones>zeros?0:1;
}

int get_rating(char buffer[BUFF_COUNT][BUFF_LENGTH], int entry_count, bool oxygen) {
	bool ignore[BUFF_COUNT] = {false};
	int line_length = strlen(buffer[0])-1;

	for(int digit = 0; digit<line_length; digit++) {
		int remaining_entries = 0; // entries that have not been eliminated
		int common = get_most_common_bit(buffer, ignore, entry_count, digit);
		if(oxygen) common = !common; // invert the most common bit if calculating oxygen
		
		// eliminate entries that don't match the bit criteria
		for(int j = 0; j < entry_count; j++)
			if(buffer[j][digit] == common+0x30 && !ignore[j]) remaining_entries++;
			else ignore[j] = true;

		// if only one entry left return it as int
		for(int j = 0; j < entry_count && remaining_entries == 1; j++) {
			if(!ignore[j])  {
				char* result = buffer[j];
				return (int) strtol(result, &result+strlen(result), 2); 
			}
		}
	}
	// shouldn't be here
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