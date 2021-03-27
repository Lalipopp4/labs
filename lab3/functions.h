#ifndef functions_h
#define functions_h

#include "table.h"

int check_table(Table* table);

int T_clear(Table* table);

char* str_data(char* d);

int T_show(Table* table);

int T_insert(Table* table);

int T_delete(Table* table);

int T_search(Table* table);

int T_read(Table* table);

int T_create(Table* table);

int inform();

void delete_table(Table* table);

#endif // functions_h