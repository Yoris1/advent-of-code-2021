#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define SUM 3
FILE *input;
char in;
int main() {
	input = fopen("input.inputfile", "r");
	// count the amount of entries in the file
	size_t entry_count = 0;
	while((in=fgetc(input)) != EOF) {
		if(in == '\n') 
			entry_count++;
	}

	// create an array where all the entries will be read into
	int *entries = malloc(entry_count*sizeof(int));
	for(int i = 0; i < entry_count; i++) {
		entries[i] = 0;
	}

	// read entries into said array
	rewind(input);
	int current_line = 0;
	while((in=fgetc(input)) != EOF) {
		if(in == '\n') {
			current_line++;
			continue;
		}
		entries[current_line] *= 10;
		entries[current_line] += in-0x30;
	}

	// count the amount of times the depth increases over the sum of SUM(set to 1 for part 1 and 3 for part 2) entries
	int depth_increase = 0;
	for(int i =1; i < entry_count; i++) {
		int last_sum = 0;
		int current_sum = 0;
		for(int j = 0; j < SUM; j++) {
			last_sum += entries[j+i-1];
			current_sum += entries[j+i];
		}
		if(last_sum < current_sum)
			depth_increase++;
	}


	printf("The depth has increased a total of %d times\n", depth_increase);
	return 0;
}