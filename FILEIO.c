#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG_ON

typedef struct CELL {
	char* contents;
} CELL;

typedef struct ROW {
	char* contents;
} ROW;

typedef struct TABLE {
	char* contents;
} TABLE;

int LEN(int x);
CELL* create_main_cell(int n, int max_width, char end_char);
//CELL* create_index_cell(int n, int max_width, char end_char);
void print_cell(CELL* c);
ROW* create_row();

int LEN(int x) {
	if (!x) return 1;
	int i;
	for (i = 0; x != 0; i++) {
		x /= 10;
	}
	return i;
}
CELL* create_main_cell(int n, int max_width, char end_char) {
	#ifdef DEBUG_ON
	printf("\nStarting <create_main_cell> for n = %d\n", n);
	#endif
	
	CELL* result = (CELL*)malloc(sizeof(CELL));
	int len, x, y;
	char* n_str = (char*)malloc(max_width * sizeof(char));
	char* content = (char*)malloc((max_width+1) * sizeof(char));
	
	len = LEN(n);
	x = (max_width - len) / 2;
	y = max_width - len - x;
	
	#ifdef DEBUG_ON
	printf("\nstart = %d, len = %d, end = %d, start+len+end = %d, max_width = %d",x,len,y,x+len+y,max_width);
	#endif
	
	sprintf(n_str, "%d", n);
	
	int i;
	for (i = 0; i < x; i++) {
		content[i] = ' ';
	}
	for (i = x; i < x + len; i++) {
		content[i] = *(n_str + (i - x));
	}
	for (i = x+len; i < x+len+y; i++) {
		content[i] = ' ';
	}
	content[max_width] = end_char;
	
	#ifdef DEBUG_ON
	printf("\n\t|");
	printf(content);
	putchar('\n');
	#endif
	
	result->contents = (char*)realloc(content, max_width+1);
	
	#ifdef DEBUG_ON
	printf("\n\t|");
	printf(result->contents);
	putchar('\n');
	printf("\nEnding <create_cell>\n");
	#endif
	
	free(n_str);

	
	return result;
	
}
/*void create_index_cell(int n, int max_width, char end_char) {
	#ifdef DEBUG_ON
	printf("\nStarting <create_index_cell> for n = %d\n", n);
	#endif
	
	CELL* result = (CELL*)malloc(sizeof(CELL));
	int len, start, end;
	char* content = (char*)malloc(max_width + 1);
	
	
	
}*/
void print_cell(CELL* c) {
	putchar('\n');
	printf(c->contents);
	putchar('\n');
}



int main() {
	
	char a = '|';
	char b = '-';
	char c = ' ';
	
	CELL* test = create_main_cell(3, 3, a);
	CELL* test2 = create_main_cell(500, 3, a);
	CELL* test3 = create_main_cell(10, 3, a);
	print_cell(test);
	print_cell(test2);
	print_cell(test3);
}




/*

X|1|2|3|4|5|6|7|8
-|----------------
1|1 2 3 4 5 6 7 8
------------------
2|2 4 6 8 10121416
------------------
3|
------------------
4|
------------------
5|
------------------
6|
------------------
7|

*/
