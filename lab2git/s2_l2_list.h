#ifndef s2_l2_list_h
#define s2_l2_list_h

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

list* new_list(list* l);

void delete_list(list* l);

#endif //s2_l2_list_h
