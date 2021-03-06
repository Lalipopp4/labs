#ifndef test.list_h
#define test.list_h

typedef struct pas{
	char* id;
	int ta;
	int ts;
	struct pas* next;
}lpas;

typedef struct list{
	int lengh;
	lpas* first;
}list;

#endif //test.list_h
