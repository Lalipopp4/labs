#include <stdio.h>
#include <stdlib.h>

#include "table.h"

Table* create_table(int msize){
	Table* table = calloc(1, sizeof(Table));
	table->msize = msize;
	table->csize = 0;
	table->ks1 = (KS1 *)malloc(msize * sizeof(KS1));
	table->ks2 = (KS2 *)malloc(msize * sizeof(KS2));
	return table;
}

int hash_1(int key){
	int hash = 0;
	while (key > 0){
		hash += key % 10;
		hash ^= hash >> 3;
		key /= 10;
	}
	return hash;
}

int hash_2(int key){
	int hash = 0;
	for (int i = 0; i < 5; i ++){
		hash += key;
		hash *= i;
		hash ^= (i >> 1);
	}
	return hash;
}

void insert_table(Table* table, int key1, char* key2, Info* info){
	int hash1 = hash_1(key1) % table->msize;
	while (table->ks1[hash1].busy == 1)
		hash1 = hash_2(hash1) % table->msize;
	int hash2 = hash_1((int)key2) % table->msize;
	Item* it = (Item *)malloc(sizeof(Item));
	it->info = (Info *)malloc(sizeof(Info));
	it->info = info;
	table->ks1[hash1].key = hash1 + 1;
	table->ks2[hash2].key = key2;
	table->ks1[hash1].busy = 1;
	table->ks1[hash1].item = it;
	table->ks1[hash1].item->key1 = hash1 + 1;
	table->ks1[hash1].item->key2 = key2;
	int rel = table->ks2[hash2].release;
	table->ks2[hash2].item = it;
	table->ks2[hash2].item[rel].key1 = hash1 + 1;
	table->ks2[hash2].item[rel].key2 = key2;
	rel++;
	printf("If this key has a parent, write it or 0 if not.\n");
	int g;
	scanf("%d%*c", &g);
	table->ks1[hash1].par = g;
}

void search_table(Table* table, int key1, char* key){
	printf("Enter type of your key.\n");
	printf("1) Integer key.\n");
	printf("2) String key.\n");
	printf("Your choice: ");
	int g;
	double n, m;
	char* f;
	scanf("%d%*c", &g);
	if (g == 1){
		printf("Enter your key: ");
		int key;
		scanf("%d%*c", &key);
		int hash = hash_1(key);
		n = table->ks1[hash].item->info->one;
		m = table->ks1[hash].item->info->two;
		f = table->ks1[hash].item->info->data;
		printf("Float numbers are %lf and %lf", n, m);
		printf("Your data is: %s", f);
	}
	else{
		printf("Enter your key: ");
		char* key;
		scanf("%s%*c", key);
		int hash = hash_1((int)key);
		for (int i= 0; i < table->ks2[hash].release; i ++){
			n = table->ks2[hash].item[i].info->one;
			m = table->ks2[hash].item[i].info->two;
			f = table->ks2[hash].item[i].info->data;
			printf("Float numbers are %lf and %lf", n, m);
			printf("Your data is: %s", f);
		}
	}
}

void read_table(Table* table){
	double n,m;
	char* f;
	for (int i = 0; i < table->msize; i ++){
		if (table->ks1[i].busy == 1){
			n = table->ks1[i].item->info->one;
			m = table->ks1[i].item->info->two;
			f = table->ks1[i].item->info->data;
			printf("First key of item: %d: \n", table->ks1[i].item->key1);
			printf("Second key of item: %s: \n", table->ks1[i].item->key2);
			printf("Float numbers are %lf and %lf", n, m);
			printf("Your data is: %s", f);
		}
	}
}
/*
void delete_item_table(Table* table){
	printf("Enter type of your key.\n");
	printf("1) Integer key.\n");
	printf("2) String key.\n");
	printf("Your choice: ");
	int g;
	scanf("%d%*c", &g);
	if (g == 1){
		printf("Enter your key: ");
		int key;
		scanf("%d%*c", &key);
		table.
	}
}

*/