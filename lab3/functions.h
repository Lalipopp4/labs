#ifndef functions_h
#define functions_h

#include "table.h"

int check_table(Table** table);

void T_clear(Table** table);

char* str_data(char* d);

void T_insert(Table** table);

void T_delete(Table** table);

void T_search(Table** table);

void T_read(Table** table);

void T_create(Table** table);

int inform();

void delete_table(Table** table);

void T_par_table(Table** table);

int data_int(char* k);

#endif // functions_h