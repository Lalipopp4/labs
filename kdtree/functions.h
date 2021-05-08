#ifndef functions_h
#define functions_h

#include "kdtree.h"

Tree* create_t();

unsigned int data_int(char d[]);

char* str_data(char d[]);

void insert_t(Tree* tree);

void clear_t(Tree* tree);

void delete_t(Tree* tree);

void search_t(Tree* tree);

void search_n_t(Tree* tree);

void read_t(Tree* tree);

int info();

#endif //functions_h