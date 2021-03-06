
#ifndef s2_l2_struct_h
#define s2_l2_struct_h

typedef struct passenger{
	char* id;
	int ta;
	int ts;
	struct passenger* next;
}pas;

typedef struct stand{
	int lengh;
	pas* pas;
	pas* first;
	pas* last;
}stand;

typedef struct queue{
	int sts;
	stand* st;
}queue;

int push_struct(pas* a, char* str, int n, int m);

int pop();

#endif //s2_l2_struct_h
