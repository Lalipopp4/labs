#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "functions.h"
#include "benchtime.h"

int main() {
	Tree* tree = NULL;
	int h;
	void (*actions[8])(Tree** tree) = {&create_t, &insert_t, &search_t, &search_n_t, &delete_t, &read_t, &clear_t, NULL};
	do{
		h = info();
		if (actions[h]) actions[h](&tree);
	}while (h < 7);
	clear_t(&tree);
	printf("Do you want to check time (0/1)?\n");
	h = int_data("Your choise: ");
	if (h) bench();
	printf("Byvayte, ihtiandry.\n");
	return 0;
}