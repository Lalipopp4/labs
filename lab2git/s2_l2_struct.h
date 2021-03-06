#ifndef test_h
#define test_h

#include "list.h"

//QUEUE
typedef struct passenger{
	char* id;
	int ta;
	int ts;
	struct passenger* next;
}pas;

typedef struct stand{
	int lengh;
	int time;
	pas* pas;
	pas* first;
	pas* last;
}stand;

typedef struct queue{
	int sts;
	stand* st;
}queue;

void push_struct(stand* a, int r, lpas* pq);

void pop_struct(stand* a, int r);

void read_struct(queue* q, int time);

void push_struct1(queue* q, int r, lpas* pq);

#endif // test_h
