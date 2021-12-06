#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define INPUT_CHAR_ARRAY 50
int8_t* add_day(int8_t* fishies, __int128_t* fish_count) {
	int new_fish_count = 0;
	for(int x = 0; x < fish_count; x++) {
		int8_t fish1, fish2;
		int_to_two_ints(fishies[x], &fish1, &fish2);
			if(fish1 == 0) {
				new_fish_count++;
			}
			if(fish2 == 0) {
				new_fish_count++;
			}
	}
	
	return NULL;
}
void int_to_two_ints(int8_t in, int8_t* a, int8_t* b) {
	*a = in&0xf;
	*b = (in>>4)&0xf;
}
void print_fish_array(int8_t* fishies, const __int128_t* length) {
	for(int i = 0 ;i < *length; i++) {
		int8_t a,b;
		int_to_two_ints(fishies[i], &a, &b);
		printf("Fish %i\n",a);
		printf("Fish %i\n",b);
	}
}

int8_t two_ints_to_one(int8_t a, int8_t b) {
	int8_t res;
	res = a;
	res += b << 4;
}
int main() {
	FILE* input_file = fopen("input.inputfile", "r");	
	char converted_buffer[INPUT_CHAR_ARRAY];
	memset(converted_buffer, 15, INPUT_CHAR_ARRAY);
	
	__int128_t i = 0;
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
	i = (i+i%2)/2;
	


	int8_t* fishes = malloc(i*sizeof(int8_t));
	int y = 0;
	for(int x = 0 ; x < i; x++) {
		int8_t fish1 = converted_buffer[y++];
		int8_t fish2 = converted_buffer[y++];
		fishes[x] = two_ints_to_one(fish1, fish2);
	}


	print_fish_array(fishes, &i);

	
	return 0;

}