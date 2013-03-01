#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char array[30000];
FILE *codefile;
char code[30000];

void shift_right(char**);
void shift_left(char**);
void increment(char**);
void decrement(char**);
void input(char**);
void output(char**);
int loop(char**, int);

int main(int argc, char* argv[]){

	/* program start */
	char *ptr=array;

	if(argc == 1){
		printf("Usage: brainfuck [filename]\n");
		exit(1);
	}
		
	/* load file */
	codefile = fopen(argv[1], "r");
	if(!codefile){
		printf("Usage: filename error\n");
	}
	/* load code */
	int pos = 0;
	while(fscanf(codefile, "%c", &code[pos]) != EOF){
		pos++;
	}

	/* run code */
	for(int i = 0; i <= pos; i++){
		switch(code[i]){
			case '>':
				shift_right(&ptr);
				break;
			case '<':
				shift_left(&ptr);
				break;
			case '+':
				increment(&ptr);
				break;
			case '-':
				decrement(&ptr);
				break;
			case '.':
				output(&ptr);
				break;
			case ',':
				input(&ptr);
				break;
			case '[':
				i = loop(&ptr, i);
				break;
			case ']':
				/* loop_end(ptr); */
				break;
		}
	}

	return 0;
}

void shift_right(char **ptr){
	(*ptr)++;
}

void shift_left(char **ptr){
	(*ptr)--;
}

void increment(char **ptr){
	(**ptr)++;
}
void decrement(char **ptr){
	(**ptr)--;
}

void output(char **ptr){
	putchar(**ptr);
}

void input(char **ptr){
	**ptr = getchar();
}

int loop(char **ptr, int pos){

	pos++;
	int rtn = pos;
	while(**ptr){
		pos = rtn;
		while(code[pos] != ']'){
			switch(code[pos]){
			case '>':
				shift_right(ptr);
				break;
			case '<':
				shift_left(ptr);
				break;
			case '+':
				increment(ptr);
				break;
			case '-':
				decrement(ptr);
				break;
			case '.':
				output(ptr);
				break;
			case ',':
				input(ptr);
				break;
			case '[':
				pos = loop(ptr, pos);
				break;
			}
			pos++;
		}
	}
	
	return pos;
}
