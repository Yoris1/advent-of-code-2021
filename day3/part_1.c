#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);

	FILE *input = fopen("input.inputfile", "r");
	int ones[24];
	int zeroes[24];
	for(int i = 0; i< 24; i++) {
		ones[i] = 0;
		zeroes[i] = 0;
	}

	int digit_length;
	char buff[24];
	while (true) {
		if(fgets(buff, 24, input) == NULL) break;

		char* end = strrchr(buff, '\n');
		if(end == NULL)
			digit_length = strlen(buff);
		else 
			digit_length = end-buff;

		for(int i = 0; i < digit_length; i++) {
			ones[i] += (buff[i] == '1'?1:0); 
			zeroes[i] += (buff[i] == '0'?1:0);
		}
	}

	int gamma = 0;
	int epsilon = 0;
	for(int i = 0; i<digit_length; i++) {
		if(ones[i] > zeroes[i])
			gamma+=(1<<(digit_length-i-1));
		else
			epsilon+=(1<<(digit_length-i-1));
	}
	printf("gamma: %d, epsilon: %d, result: %d\n", gamma, epsilon, gamma*epsilon);

}