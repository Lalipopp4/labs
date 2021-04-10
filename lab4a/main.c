#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "functions.h"

int main() {
	Tree* tree = NULL;
	create_tree(tree);
	int h;
	void (*actions[8])(Tree** tree) = {&insert_t, &search_t, &delete_t, &read_t, &clear_t, NULL};
	do{
		h = info();
		if (actions[h]) actions[h](&tree);
	}while (h < 5);
}