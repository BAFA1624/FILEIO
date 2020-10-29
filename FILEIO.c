#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG_ON

typedef struct CELL {
	int size;
	int capacity;
	char* contents;
} CELL;

typedef struct ROW {
	int size;
	int capacity;
	CELL** contents;
} ROW;

typedef struct TABLE {
	int size;
	int capacity;
	ROW** contents;
} TABLE;

int LEN(int x);
CELL* create_cell(int n, int max_width, char end_char);
void print_cell(CELL* c);
ROW* create_row(int capacity);
void add_cell(ROW* target, CELL* new_cell);
void print_row(ROW* r);

int LEN(int x) {
	if (!x) return 1;
	int i;
	for (i = 0; x != 0; i++) {
		x /= 10;
	}
	return i;
}
CELL* create_cell(int n, int max_width, char end_char) {
	#ifdef DEBUG_ON
	printf("\nStarting <create_main_cell> for n = %d\n", n);
	#endif
	
	CELL* result = (CELL*)malloc(sizeof(CELL));
	int len, x, y;
	char* n_str = (char*)malloc(max_width * sizeof(char));
	result->contents = (char*)malloc((max_width+2) * sizeof(char));
	
	len = LEN(n);
	x = (max_width - len) / 2;
	y = max_width - len - x;
	
	#ifdef DEBUG_ON
	printf("\nstart = %d, len = %d, end = %d, start+len+end = %d, max_width = %d",x,len,y,x+len+y,max_width);
	#endif
	
	sprintf(n_str, "%d", n);
	
	int i;
	for (i = 0; i < x; i++) {
		*(result->contents + i) = ' ';
	}
	for (i = x; i < x + len; i++) {
		*(result->contents + i) = *(n_str + (i - x));
	}
	for (i = x+len; i < x+len+y; i++) {
		*(result->contents + i) = ' ';
	}
	result->contents[max_width] = end_char;
	result->contents[max_width+1] = '\0';
	
	result->size = max_width + 1;
	result->capacity = max_width + 2;
	
	#ifdef DEBUG_ON
	printf("\n\t|");
	printf(result->contents);
	putchar('\n');
	printf("\nEnding <create_cell>\n");
	#endif
	
	free(n_str);
	
	return result;
	
}
void print_cell(CELL* c) {
	printf(c->contents);
	putchar('\n');
}
ROW* create_row(int capacity) {
	
	#ifdef DEBUG_ON
	printf("\nStarting <create_row> with capacity of %d\n", capacity);
	#endif
	
	ROW* result = (ROW*)malloc(sizeof(ROW));
	if (!result) {
		printf("\nMem alloc for row failed, exiting program.\n");
		exit(1);
	}
	
	result->size = 0;
	result->capacity = capacity;
	result->contents = (CELL**)malloc(capacity * sizeof(CELL*));
	if (!result->contents) {
		printf("\nMem alloc for row->contents failed, exiting program.\n");
		exit(1);
	}
	
	return result;
	
}
void add_cell(ROW* target, CELL* new_cell) {
	#ifdef DEBUG_ON
	printf("\nStarting <add_cell>\n");
	#endif
	if (target->size < target->capacity) {
			target->contents[target->size] = new_cell;
			target->size++;
			#ifdef DEBUG_ON
			printf("\n\tSuccessfully added new_cell. Ending <add_cell>\n");
			#endif
	} else {
		#ifdef DEBUG_ON
		printf("\nRow already full, skipping add. Ending <add_cell>\n");
		#endif
		return;
	}
}
char* create_row_str(ROW* r) {
	int length = 0;
	for (int i = 0; i < r->size; i++) {
		length += (*(r->contents + i))->size;
	}
	char* result = (char*)malloc((length + 1) * sizeof(char));
	
	
	
}
TABLE* create_table(int capacity) {
	
	#ifdef DEBUG_ON
	printf("\nStarting <create_table>\n");
	#endif
	
	TABLE* result = (TABLE*)malloc(sizeof(TABLE));
	if (!result) {
		printf("\nFailed to allocate memory for table.\n");
		exit(1);
	}
	
	result->size = 0;
	result->capacity = capacity;
	result->contents = (ROW**)malloc(capacity * sizeof(ROW*));
	if (!result->contents) {
		printf("\nFailed to allocate memory for table->contents of capacity %d.\n", capacity);
		exit(1);
	}
	
	#ifdef DEBUG_ON
	printf("\nEnding <create_table>\n");
	#endif
	
	return result;
	
}
void add_row(TABLE* target, ROW* new_row) {
	#ifdef DEBUG_ON
	printf("\nStarting <add_row>");
	#endif
	if (target->size < target->contents) {
		target->contents[target->size] = new_row;
		target->size++;
		#ifdef DEBUG_ON
		printf("\nEnding <add_row>");
		#endif
		return;
	} else {
		#ifdef DEBUG_ON
		printf("\nTable already full, skipping row. Ending <add_row>");
		#endif
		return;
	}
}

void print_row(ROW* r) {
	for (int i = 0; i < r->size; i++) {
		printf((*(r->contents + i))->contents);
	}
	putchar('\n');
}

int main() {
	
	


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
