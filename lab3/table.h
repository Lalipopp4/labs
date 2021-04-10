#ifndef table_h
#define table_h

typedef struct info{
	int release;
	double one;
	double two;
	char* data;
}Info;

typedef struct item{
	int key1;
	char* key2;
	Info* info;
	struct item* next;
}Item;

typedef struct keyspace1{
	int key;
	int par;
	int busy;
	Item* item;
	Item* first;
}KS1;

typedef struct keyspace2{
	char* key;
	Item* item;
	int busy;
	Item* first;
}KS2;

typedef struct table{
	int size;
	KS1* ks1;
	KS2* ks2;
	int* ks1_size;
	int* ks2_size;
}Table;

Table* create_table(int size);

void insert_table(Table* table);

Item* search_table(Table* table, int key1, char* key2);

void read_table(Table* table);

void delete_item_table(Table* table, int key1, char* key2);

void ks1_search_read_table(Table* table, int key);

void ks2_search_read_table(Table* table, char* key);

Item* ks1_search_table(Table* table, int key);

Item* ks2_search_table(Table* table, char* key);

void clear_table(Table* table);

void ks1_delete_item_table(Table* table, int key);

void ks2_delete_item_table(Table* table, char* key);

void delete_item_table(Table* table, int key1, char* key2);

Table* parent_table(Table* table, Table* par_table);

#endif //table_h
