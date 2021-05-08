#include <stdio.h>

#include "kdtree.h"
#include "functions.h"

int main(){
	Tree* tree = NULL;
	tree = create_t();
	void (*actions[7])(Tree** tree) = {&insert_t, &search_t, &read_t, &delete_t, &search_n_t, &clear_t, NULL};
	int h;
	do{
		h = info();
		if (actions[h]) actions[h](&tree);
	}while (h < 5);
	printf("I don't know hot to say goodbye so go away.\n");
	return 0;
}