#include <stdlib.h>
#include <stdio.h>

void move_ship(int* x, int* y, char* command, int end) {
	int move_by = command[end]-0x30;
	switch (command[0])
	{
		case 'f':
			*x+=move_by;
			break;
		case 'b':
			*x-=move_by;
			break;
		case 'u':
			*y+=move_by;
			break;
		case 'd':
			*y-=move_by;
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
	int y = 0;

	char i = 0;
	char *line = malloc(sizeof(char) * 24);
	char ch;
	while(1) 
	{
		ch = getc(input);
		if(ch == '\n' || ch == EOF) {
			move_ship(&x, &y, line, i-1);
			i = 0;
			if(ch == EOF) break;
			continue;
		}
		line[i++] = ch;
	}

	printf("Ship x(horizontal pos): %d; y: %d depth(-y): %i; result: %d\n", x, y, -y, -y*x);

	return 0;
}