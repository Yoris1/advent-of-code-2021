#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void move_ship(const char* command, int* x, int* depth, int* aim) {
	int move_by = strchr(command, ' ')[1]-0x30;
	switch (command[0])
	{
		case 'f': *x+=move_by; *depth+= (*aim)*move_by; break;
		case 'u': *aim-=move_by; break;
		case 'd': *aim += move_by; break;
	}
	return;
}

int main() {
	FILE *input = fopen("input.inputfile", "r");

	int x = 0, depth = 0, aim = 0;
	char line[24];
	while(fgets(line, 24, input)!=NULL)
		move_ship(line, &x, &depth, &aim);
	
	fclose(input);
	printf("x: %d, depth: %i, aim: %d, result: %d\n", x, depth, aim, depth*x);
	return 0;
}