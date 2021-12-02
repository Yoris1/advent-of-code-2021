#include <stdlib.h>
#include <stdio.h>

void move_ship(int* x, int* depth, int* aim, char* command, int end) {
	int move_by = command[end]-0x30;
	switch (command[0])
	{
		case 'f':
			*x+=move_by;
			*depth+= (*aim)*move_by;
			break;
		case 'u':
			*aim-=move_by;
			break;
		case 'd':
			*aim += move_by;
			break;
		default:
			break;
	}
	return;
}

FILE* input;

int main() {
	input = fopen("input.inputfile", "r");

	int x = 0;
	int depth = 0;
	int aim = 0;

	char i = 0;
	char *line = malloc(sizeof(char) * 24);
	char ch;
	while(1) 
	{
		ch = getc(input);
		if(ch == '\n' || ch == EOF) {
			move_ship(&x, &depth, &aim, line, i-1);
			i = 0;
			if(ch == EOF) break;
			continue;
		}
		line[i++] = ch;
	}

	printf("Ship horizontal pos: %d; depth: %i; aim: %d result: %d\n", x, depth, aim, depth*x);
	return 0;
}