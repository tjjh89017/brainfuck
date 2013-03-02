#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 65536

char array[MAX_SIZE];
char code[MAX_SIZE];
FILE *codefile;

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
	int size = 0;
	while(fscanf(codefile, "%c", &code[size]) != EOF){
		size++;
	}

	/* run code */
	int loop = 1;
	for(int pos = 0; pos <= size; pos++){
		switch(code[pos]){
			case '>':
				ptr++;
				break;
			case '<':
				ptr--;
				break;
			case '+':
				++*ptr;
				break;
			case '-':
				--*ptr;
				break;
			case '.':
				putchar(*ptr);
				break;
			case ',':
				*ptr = getchar();
				break;
			case '[':
				if(*ptr == 0){
					loop = 1;
					while(loop > 0){
						pos++;
						if(code[pos] == '[')
							loop++;
						else if(code[pos] == ']')
							loop--;
					}
				}
				break;
			case ']':
				loop = 1;
				while(loop > 0){
					pos--;
					if(code[pos] == '[')
						loop--;
					else if(code[pos] == ']')
						loop++;
				}
				pos--;
				break;
		}
	}

	return 0;
}
