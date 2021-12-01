#include <stdio.h>
FILE *input;
char in;
int main() {
	input = fopen("input.inputfile", "r");

	int depth_increase = 0;

	int last_number = -1;
	int number = 0;
	
	while((in=fgetc(input)) != EOF) {
		if(in=='\n') {
			if(last_number < number && last_number != -1)
				depth_increase++;
			last_number = number;
			number = 0;
			continue;
		}
		number *= 10;
		number += in-48;
	}
	printf("The depth has increased a total of %d times", depth_increase);
	return 0;
}
