#ifndef table_h
#define table_h

typedef struct info{
	double one;
	double two;
	char* data;
}Info;

typedef struct item{
	int k2size;
	int size;
	int pos;
	int busy;
	struct item* next;
}Item;

typedef struct item_copy{
	int key1;
	char* key2;
	int k2size;
	Info* info;
	int size;
	int pos;
	int busy;
	struct item* next;
}Item_c;

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
	char* file;
	int pos;
	int size;
	KS1* ks1;
	KS2* ks2;
	int* ks1_size;
	int* ks2_size;
}Table;

Table* create_table(int size);

void insert_table(Table* table, int key1, char* key2);

void search_table(Table* table, int key1, char* key2);

void read_table(Table* table);

void delete_item_table(Table* table, int key1, char* key2);

Item_c* ks1_search_table(Table* table, int key);

Item_c* ks2_search_table(Table* table, char* key);

void clear_table(Table* table);

void ks1_delete_item_table(Table* table, int key);

void ks2_delete_item_table(Table* table, char* key);

void delete_item_table(Table* table, int key1, char* key2);

Table* parent_table(Table* table, Table* par_table);

#endif //table_h
