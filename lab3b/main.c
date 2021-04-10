#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "table.h"
#include "functions.h"

int main(){
	Table *table = NULL;
	void (*actions[6])(Table* table) = {&T_create, &T_insert, &T_search, &T_read, &T_delete, &T_clear, &T_par_table};
	int h;
	do{
		h = inform();
		if (actions[h]) actions[h](table);
	}while (h != 6); 
	delete_table(table);
	printf("Aufwidersehen!\n");
	return 0;
}