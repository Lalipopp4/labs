#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"
#include "functions.h"

Table* create_table(int size){
	Table* table = NULL;
	table = calloc(1, sizeof(Table));
	table->size = size;
	int* s1;
	s1 = (int *)malloc(table->size * sizeof(int));
	table->ks1_size = s1;
	int* s2;
	s2 = (int *)malloc(table->size * sizeof(int));
	table->ks2_size = s2;
	for (int i= 0; i < size; i ++){
		table->ks1_size[i] = 0;
		table->ks2_size[i] = 0;
	}
	KS1* ks1;
	ks1 = (KS1 *)malloc(size * sizeof(KS1));
	table->ks1 = ks1;
	KS2* ks2;
	ks2 = (KS2 *)malloc(size * sizeof(KS2));
	table->ks2 = ks2;
	return table;
}

int prime(int n){
	int g = n - 1, h = 0;
	while (g > 1){
		for (int i = 2; i < (g + 1) / 2; i ++){
			if (g % i == 0){
				h = 1;
				break;
			}
		}
		if (h == 1) break;
		g--;
	}
	return g;
}

int hash_1(int key, int n){
	return key % n;
}

int hash_2(int key, int n){
	int pr = prime(n) * key + 1;
	return pr;
}

void insert_table(Table* table){
	int k = 0;
	int size = table->size;
	for (int i = 0; i < size; i ++){
		k += table->ks1_size[i];
	}
	if (k == size) {
		printf("No more memory in table.\n");
		return ;
	}
	int key1;
	key1 = data_int("Enter first key: ");
	char* key2;
	key2 = str_data("Enter second key: ");
	int hash1 = hash_1(key1, size);
	int m, e, u;
	m = table->ks1[hash1].busy;
	e = table->ks1[hash1].key;
	while (m && e != key1){
		hash1 = ((hash1 + hash_2(key1, size)) % size);
	}
	int hash2 = hash_1((int)key2, size);
	u = table->ks2[hash2].busy;
	KS2* q;
	q = table->ks2;
	while (u && (int)(q[hash2].key) != (int)key2){
		hash2 = ((hash2 + hash_2((int)key2, size)) % size);
	}
	if (m && u){
		printf("This composite key already exists.\n");
		return ;
	}
	Item* it;
	it = (Item*)calloc(1, sizeof(Item));
	Info* info; 
	info = (Info *)malloc(sizeof(Info));
	it->info = info;
	Item* iit;
	it->info->data = str_data("Enter string data: ");
	int h = 2;
	do{
		if (h != 2) scanf("%*s");
		printf("Enter two float numbers: ");
		h = scanf("%lf %lf%*c", &it->info->one, &it->info->two);
	}while (h != 2);
	it->key1 = key1;
	it->key2 = key2;
	table->ks1[hash1].item = it;
	if (table->ks1_size[hash1] == 0){
		table->ks1[hash1].first = table->ks1[hash1].item;
		table->ks1[hash1].key = key1;
		table->ks1[hash1].busy = 1;
	}
	table->ks2[hash2].item = it;
	if (table->ks2_size[hash2] == 0){
		table->ks2[hash2].first = table->ks2[hash2].item;
		table->ks2[hash2].key = key2;
		table->ks2[hash2].busy = 1;
	}
	iit = table->ks1[hash1].item;
	table->ks1[hash1].item->next = NULL;
	table->ks1[hash1].item = table->ks1[hash1].item->next;
	iit->next = table->ks1[hash1].item;
	iit = table->ks2[hash2].item;
	table->ks2[hash2].item->next = NULL;
	table->ks2[hash2].item = table->ks2[hash2].item->next;
	iit->next = table->ks2[hash2].item;
	table->ks1_size[hash1]++;
	table->ks2_size[hash2]++;
	int g, b = 0, n = 1;
	do{
		if (n != 1) scanf("%*s");
		printf("If this key has a parent, write it or 0 if not.\n");
		printf("Your choice: ");
		n = scanf("%d%*c", &g);
		for (int j = 0; j < table->size; j ++){
			if (table->ks1[j].key && table->ks1[j].key == g){
				b = 1;
			}
		}
	}while(n != 1);
	if (b == 1)
		table->ks1[hash1].par = g;
	else
		printf("No items with this key.\n");
}

Item* ks1_search_table(Table* table, int key){
	int r = table->size;
	int hash = hash_1(key, r) % table->size;
	while (table->ks1[hash].busy && table->ks1[hash].key != key){
		hash = ((hash + hash_2(key, r)) % r);
	}
	if (!(table->ks1[hash].busy)) return NULL;
	Item* it = table->ks1[hash].first;
	return it;
}

Item* ks2_search_table(Table* table, char* key){
	int r = table->size;
	int hash = hash_1((int)key, r);
	while (table->ks2[hash].busy && (int)table->ks2[hash].key != (int)key){
		hash = ((hash + hash_2((int)key, r)) % r);
	}
	if (!(table->ks2[hash].busy)) return NULL;
	double n,m;
	char* f;
	Item* it = table->ks2[hash].first;
	return it;
}

Item* search_table(Table* table, int key1, char* key2){
	double n, m;
	char *f;
	int r = table->size;
	int hash1 = hash_1(key1, r);
	while (table->ks1[hash1].busy && table->ks1[hash1].key != key1){
		hash1 = ((hash1 + hash_2(key1, r)) % r);
	}
	Item* it = table->ks1[hash1].first;
	while ((int)it->key2 != (int)key2){
		it = it->next;
	}
	return it;
}

void read_table(Table* table){
	double n,m;
	for (int i = 0; i < table->size; i ++){
		if (!(table->ks1_size[i])) continue;
		Item* it = table->ks1[i].first;
		for (int j = 0; j < table->ks1_size[i]; j ++){
			n = it->info->one;
			m = it->info->two;
			printf("\nElement with keys: %d and %s.\n", it->key1, it->key2);
			printf("Float numbers are %lf and %lf\n", n, m);
			printf("Your data is: %s\n", it->info->data);
			it = it->next;
		}
	}
}

void ks1_delete_item_table(Table* table, int key){
	int r = table->size;
	int hash = hash_1(key, r);
	while (table->ks1[hash].busy && table->ks1[hash].key != key){
		hash = ((hash + hash_2(key, r)) % r);
	}
	if (!(table->ks1[hash].busy)){
		printf("No item in table.\n");
		return ;
	}
	Item* it = table->ks1[hash].first;
	for (int i = 0; i < table->ks1_size[hash]; i ++){
		int hash2 = hash_1((int)it->key2, r);
		while ((int)table->ks2[hash2].key != (int)table->ks2[hash2].key){
			hash2 = ((hash2 + hash_2((int)it->key2, r)) % r);
		}
		Item* iit = table->ks2[hash2].first;
		Item* pit;
		int j = 0;
		for (; j < table->ks2_size[hash2]; j ++){
			pit = iit;
			if (iit->key1 == it->key1 && (int)(iit->key2) == (int)(it->key2)) break;
			iit = iit->next;
		}
		if (j + 1 < table->ks2_size[hash2])
			pit->next = iit->next;
		free(it->key2);
		free(it->info->data);
		free(it->info);
		free(it);
		table->ks1[hash].first = NULL;
		it = it->next;
		table->ks2_size[hash2] --;
		if (table->ks2_size[hash2] == 0) table->ks2[hash2].busy = 0;
	}
	for (int i = 0; i < table->size; i ++){
		if (table->ks1[hash].par == key)
			table->ks1[hash].par = 0;
	}
	table->ks1[hash].busy = 0;
	table->ks1_size[hash] = 0;
}

void ks2_delete_item_table(Table* table, char* key){
	int r = table->size;
	int hash = hash_1((int)key, r);
	puts("YY");
	while ((int)table->ks2[hash].key != (int)key){
		hash = ((hash + hash_2((int)key, r)) % r);
	}
	puts("GG");
	Item* it = table->ks2[hash].first;
	for (int i = 0; i < table->ks2_size[hash]; i ++){
		int hash1 = hash_1(it->key1, r);
		while ((table->ks1[hash1].key) != it->key1){
			hash1 = ((hash1 + hash_2(it->key1, r)) % r);
		}
		Item* iit = table->ks1[hash1].first;
		Item* pit;
		int j = 0;
		for (; j < table->ks1_size[hash1]; j ++){
			if (iit->key1 == it->key1 && (int)(iit->key2) == (int)(it->key2)) break;
			pit = iit;
			iit = iit->next;
		}
		if (j + 1 < table->ks1_size[hash1])
			pit->next = iit->next;
		free(it->key2);
		free(it->info->data);
		free(it->info);
		free(it);
		table->ks2[hash].first = NULL;
		it = it->next;
		table->ks1_size[hash1] --;
		if (table->ks1_size[hash1] == 0) table->ks1[hash1].busy = 0;
		it = NULL;
		it = it->next;
	}
	table->ks1[hash].busy = 0;
	table->ks1_size[hash] = 0;
}

void delete_item_table(Table* table, int key1, char* key2){
	int r = table->size;
	int hash1 = hash_1(key1, r);
	while (table->ks1[hash1].key != key1){
		hash1 = ((hash1 + hash_2(key1, r)) % r);
	}
	puts("RR");
	int hash2 = hash_1((int)key2, r);
	while ((int)table->ks2[hash2].key != (int)key2){
		hash2 = ((hash2 + hash_2((int)key2, r)) % r);
	}
	puts("FF");
	Item* it1 = table->ks1[hash1].first;
	Item* it2 = table->ks1[hash2].first;
	Item* pit1;
	Item* pit2;
	int j = 0;
	for (; j < table->ks1_size[hash1]; j ++){
		if ((int)it1->key2 == (int)key2) break;
			pit1 = it1;
			it1 = it1->next;
	}
	int i = 0;
	for (; i < table->ks2_size[hash2]; i ++){
		if (it2->key1 == key1) break;
			pit2 = it2;
			it2 = it2->next;
	}
	if (j + 1 < table->ks1_size[hash1])
		pit1->next = it1->next;
	if (i + 1 < table->ks2_size[hash2]){
		pit2->next = it2->next;
	}
	if (j == 0)
		table->ks1[hash1].first = it1->next;
	if (i == 0)
		table->ks2[hash2].first = it2->next;
	free(it1->key2);
	free(it1->info->data);
	free(it1->info);
	free(it1);
	table->ks1_size[hash1] --;
	table->ks2_size[hash2] --;
	it2 = NULL;
}

void clear_table(Table* table){
	for (int i = 0; i < table->size; i ++){
		if (table->ks1_size[i]){
			Item* it = table->ks1[i].first;
			for (int j = 0; j < table->ks1_size[i]; j ++){
				free(it->key2);
				free(it->info->data);
				free(it->info);
				free(it);
				it = it->next;
			}
		}
		if (table->ks2_size[i]){
			free(table->ks2[i].key);
		}
	}
	free(table->ks1);
	free(table->ks2);
	free(table->ks1_size);
	free(table->ks2_size);
	free(table);
	table = NULL;
	printf("Table was successfully removed.\n");
}

Table* parent_table(Table* table, Table* par_table){
	par_table = (Table *)calloc(1, sizeof(table));
	par_table->ks1 = (KS1 *)malloc(sizeof(KS1));
	for (int i = 0; i < table->size; i ++){
		if (!table->ks1_size[i]) continue;
		if (!table->ks1[i].par) continue;
		Item* it = table->ks1[i].first;
		par_table->size ++;
		par_table->ks1_size[i] = table->ks1_size[i];
		for(int j = 0; j < table->ks1_size[i]; j ++){
			if (j == 0)
				par_table->ks1[i].first = it;
			par_table->ks1[i].item = it;
			par_table->ks1[i].item->info = it->info;
			par_table->ks1[i].item->key1 = it->key1;
			par_table->ks1[i].item->key2 = it->key2;
		}
	}
	return par_table;
}