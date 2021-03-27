#ifndef table_h
#define table_h

typedef struct info{
	double one;
	double two;
	char* data;
}Info;
/*
typedef struct intfor{
	int release;
	Info info;
}InfoR;
*/
typedef struct item{
	int key1;
	char* key2;
	int release;
	Info* info;
}Item;

typedef struct keyspace1{
	int key;
	int par;
	int busy;
	Item* item;
}KS1;

typedef struct keyspace2{
	char* key;
	int release;
	Item* item;
}KS2;

typedef struct table{
	int msize;
	int csize;
	KS1* ks1;
	KS2* ks2;
}Table;

Table* create_table(int msize);

void insert_table(Table* table, int key1, char* key2, Info* info);

void search_table(Table* table, int key1, char* key2);

void read_table(Table* table);

void delete_item_table(Table* table, int key1, char* key2);

#endif //table_h
