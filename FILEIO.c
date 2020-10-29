#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
	
//#define DEBUG_ON

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
	int rows;
	int columns;
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
CELL* create_corner_cell(int max_width) {
	
	CELL* result = (CELL*)malloc(sizeof(CELL));
	result->contents = (char*)malloc( (max_width + 2) * sizeof(char) );
	result->size = 0;
	result->capacity = max_width + 2;

	*(result->contents + max_width) = '|';
	*(result->contents + max_width + 1) = '\0';

	for (int i = 0; i < max_width; i++) {
		if (max_width % 2 == 0) {
			if (max_width / 2 == i) {
				*(result->contents + i) = 'X';
			} else {
				*(result->contents + i) = ' ';
			}
			result->size++;
		} else {
			if ((max_width / 2)-1 == i || max_width / 2 == i) {
				*(result->contents + i) = 'X';
			} else {
				*(result->contents + i) = ' ';
			}
			result->size++;
		}
	}
	result->size++;

	return result;
}
void clear_cell(CELL* c) {
	free(c->contents);
	c->contents = (char*)malloc(c->capacity * sizeof(char));
	c->size = 0;
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
	int i, j;
	CELL* current;

	for (i = 0; i < r->size; i++) {
		length += (*(r->contents + i))->size;
	}

	char* result = (char*)malloc((length + 1) * sizeof(char));
	int size = 0;

	for (i = 0; i < r->size; i++) {
		current = *(r->contents + i);
		for (j = 0; j < current->size; j++) {
			*(result + size) = *(current->contents + j);
			size++;
		}
	}

	return result;
	
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
	printf("\nStarting <add_row>\n");
	#endif
	if (target->size < target->capacity) {
		target->contents[target->size] = new_row;
		target->size++;
		#ifdef DEBUG_ON
		printf("\nEnding <add_row>\n");
		#endif
		return;
	} else {
		#ifdef DEBUG_ON
		printf("\nTable already full, skipping row. Ending <add_row>\n");
		#endif
		return;
	}
}
void clear_row(ROW* r) {
	free(r->contents);
	r->contents = (CELL**)malloc(r->capacity * sizeof(CELL*));
	r->size = 0;
}

void print_row(ROW* r) {
	for (int i = 0; i < r->size; i++) {
		printf((*(r->contents + i))->contents);
	}
	putchar('\n');
}
void print_table(TABLE* t) {
	for (int i = 0; i < t->size; i++) {
		print_row(*(t->contents + i));
	}
}


TABLE* create_times_table(int n, int m) {
	int i, j;
	char space, vert_line;
	CELL* c;
	ROW* r;

	space = ' ';
	vert_line = '|';

	int max_nm = n * m;
	int max_width = LEN(max_nm);

	TABLE* t = create_table((n + 2) * (m + 1));	// Create a table with one extra column and two extra rows; n = rows, m = columns
	t->rows = n;
	t->columns = m;
	r = create_row(m+1);
	

	for (i = 0; i < m+1; i++) {
		if (i > 0) {
			c = create_cell(i, max_width, vert_line);
			add_cell(r, c);
		} else {
			c = create_corner_cell(max_width);
			add_cell(r, c);
		}
		
	}
	
	add_row(t, r);
	c = (CELL*)malloc(sizeof(CELL));
	c->size = 0; 
	c->capacity = max_width+1;
	c->contents = (char*)malloc(c->capacity * sizeof(char));
	r = create_row(m+1);

	for (i = 0; i < m+1; i++) {
		for(j = 0; j < max_width+1; j++) {
			*(c->contents + j) = '-';
		}
		*(c->contents + max_width+1) = '\0';
		add_cell(r, c);
	}

	add_row(t, r);
	r = create_row(m+1);

	for (i = 1; i < n+1; i++) {
		#ifdef DEBUG_ON
		printf("\n\tCreating row for multiples of %d.\n", i);
		#endif

		for (j = 0; j < m+1; j++) {
			if (j > 0) {
				c = create_cell(i*j, max_width, space);
				add_cell(r, c);
			} else {
				c = create_cell(i, max_width, vert_line);
				add_cell(r, c);
			}

		}
		
		add_row(t, r);
		r = create_row(m+1);
	}

	return t;

}
char* TABLEtoSTR(TABLE* t) {
	int size, i, j, k;
	int count = 0;
	ROW* current_row;
	CELL* current_cell;

	int n_rows = t->size;
	int n_cells = (*(t->contents))->size;
	int cell_size = (*(*(t->contents))->contents)->size;

	size = (n_rows)*(n_cells * cell_size + 1);

	char* result = (char*)malloc((size+1) * sizeof(char));

	for (i = 0; i < t->size; i++) {
		current_row = *(t->contents + i);
		for (j = 0; j < current_row->size; j++) {
			current_cell = *(current_row->contents + j);
			for (k = 0; k < current_cell->size; k++) {
				*(result + count) = *(current_cell->contents + k);
				count++;
			}
		}
		*(result + count) = '\n';
		count++;
	}
	*(result + size) = '\0';

	return result;

}

void write_table_to_file(TABLE* t) {
	
	int x = LEN(t->rows);
	int y = LEN(t->columns);

	char* filename = (char*)malloc((x+y+6) * sizeof(char));
	sprintf(filename,"%dx%d.txt", t->rows, t->columns);

	FILE* target;
	target = fopen(filename, "w");

	fprintf(target, TABLEtoSTR(t));

	fclose(target);

}

int main(int argc, char* argv[]) {
	
	if (argc > 2) {
		
		int x = atoi(argv[1]);
		int y = atoi(argv[2]);
		TABLE* t = create_times_table(x, y);
		write_table_to_file(t);

	} else {
		printf("\nPlease provide two numbers to turn into a table. Format: ./FILEIO {n1} {n2}\n");
	}

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
