#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "table.h"
#include "functions.h"

int main(){
	Table *table = NULL;
	int i = 0;
	void (*actions[8])(Table** table) = {&T_create, &T_insert, &T_search, &T_delete, &T_read, &T_clear, &T_par_table, NULL};
	int h;
	do{
		h = inform();
		
		if (actions[h])
			actions[h](&table);

	}while (h < 6); 
	delete_table(&table);
	printf("Aufwidersehen!\n");
	return 0;
}