#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"
#include "functions.h"

Table* create_table(int size){
	Table* table = NULL;
	table = calloc(1, sizeof(Table));
	table->size = size;
	table->ks1_size = (int *)calloc(table->size, sizeof(int));
	table->ks2_size = (int *)calloc(table->size, sizeof(int));
	for (int i= 0; i < size; i ++){
		table->ks1_size[i] = 0;
		table->ks2_size[i] = 0;
	}
	table->ks1 = (KS1 *)calloc(size, sizeof(KS1));
	table->ks2 = (KS2 *)calloc(size, sizeof(KS2));
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
	char* key2 = NULL;
	key2 = str_data("Enter second key: ");
	int hash1 = hash_1(key1, size);
	while (table->ks1[hash1].busy && table->ks1[hash1].key != key1){
		hash1 = ((hash1 + hash_2(key1, size)) % size);
	}
	Item* it = NULL;
	if (table->ks1[hash1].busy) it = table->ks1[hash1].first;
	while (it){
		if (*it->key2 == *key2){
			printf("This composite key already exists.\n");
			return ;
		}
		it = it->next;
	}
	it = NULL;
	
	int hash2 = hash_1(*key2, size);
	while (table->ks2[hash2].busy && *table->ks2[hash2].key!= *key2){
		hash2 = ((hash2 + hash_2(*key2, size)) % size);
	}/*
	if (table->ks1[hash1].busy && table->ks2[hash2].busy){
		printf("%d %s\n", table->ks1[hash1].key, table->ks2[hash2].key);
		printf("This composite key already exists.\n");
		return ;
	}*/
	
	if (table->ks1_size[hash1] == 0){
		it = (Item *)malloc(sizeof(Item));
		it->next = NULL;
		it->key2 = key2;
		it->info.data = NULL;
		it->info.data = str_data("Enter string data: ");
		it->key1 = key1;
		int h = 2;
		do{
			if (h != 2) scanf("%*s");
			printf("Enter two float numbers: ");
			h = scanf("%lf %lf%*c", &it->info.one, &it->info.two);
		}while (h != 2);
		table->ks1[hash1].first = it;
		table->ks1[hash1].cur = it;
		table->ks1[hash1].key = key1;
		table->ks1[hash1].busy = 1;
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
	else{
		it = table->ks1[hash1].cur;
		it->next = (Item *)malloc(sizeof(Item));
		it->next->info.data = NULL;
		it->next->info.data = str_data("Enter string data: ");
		int h = 2;
		do{
			if (h != 2) scanf("%*s");
			printf("Enter two float numbers: ");
			h = scanf("%lf %lf%*c", &it->next->info.one, &it->next->info.two);
		}while (h != 2);
		it->next->key1 = key1;
		it->next->key2 = key2;
		//it->next->key2 = (char *)malloc(sizeof(key2));
		//strcpy(it->next->key2, key2);
		it = it->next;
		table->ks1[hash1].cur = it;
	}
	if (table->ks2_size[hash2] == 0){
		table->ks2[hash2].first = it;
		table->ks2[hash2].cur = it;
		table->ks2[hash2].key =  key2;
		table->ks2[hash2].busy = 1;
	}
	else{
		table->ks2[hash2].cur->next = it;
		table->ks2[hash2].cur = it;
	}
	table->ks1_size[hash1]++;
	table->ks2_size[hash2]++;
}

Item* ks1_search_table(Table* table, int key){
	int r = table->size;
	int hash = hash_1(key, r) % r;
	while (table->ks1[hash].busy && table->ks1[hash].key != key){
		hash = ((hash + hash_2(key, r)) % r);
	}
	if (!(table->ks1[hash].busy)) return NULL;
	Item* it = NULL;
	printf("Found!\n");
	it = (Item *)malloc(table->ks1_size[hash] * sizeof(Item));
	Item* itt = table->ks1[hash].first;
	for (int i = 0; i < table->ks1_size[hash]; i ++){
		it[i].info.data = (char *)malloc(sizeof(itt->info.data));
		it[i].key2 = (char *)malloc(sizeof(itt->key2));
		it[i].key1 = itt->key1;
		it[i].info.one = itt->info.one;
		it[i].info.two = itt->info.two;
		strcpy(it[i].key2, itt->key2);
		strcpy(it[i].info.data, itt->info.data);
		itt = itt->next;
	}
	return it;
}

Item* ks2_search_table(Table* table, char* key){
	int r = table->size;
	int hash = hash_1(*key, r);
	puts("VV");
	while (table->ks2[hash].busy && *table->ks2[hash].key != *key){
		puts("EE");
		hash = ((hash + hash_2(*key, r)) % r);
	}
	puts("RR");
	if (!(table->ks2[hash].busy)) return NULL;
	Item* it = NULL;
	printf("Found!\n");
	printf("%d\n",table->ks2_size[hash]);
	it = (Item *)malloc(table->ks2_size[hash] * sizeof(Item));
	Item* itt = table->ks2[hash].first;
	for (int i = 0; i < table->ks2_size[hash]; i ++){
		it[i].info.data = (char *)malloc(sizeof(itt->info.data));
		it[i].key2 = (char *)malloc(sizeof(itt->key2));
		it[i].key1 = itt->key1;
		it[i].info.one = itt->info.one;
		it[i].info.two = itt->info.two;
		strcpy(it[i].key2, itt->key2);
		strcpy(it[i].info.data, itt->info.data);
		itt = itt->next;
	}
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
	puts("ZZ");
	if (!(table->ks1[hash1].busy)) return NULL;
	Item* itt = table->ks1[hash1].first;
	Item* it = NULL;
	puts("FF");
	while (itt->next && *itt->key2 != *key2){
		itt = itt->next;
	}
	printf("%s\n", itt->key2);
	printf("Found!\n");
	it = (Item *)malloc(sizeof(Item));
	it->info.data = (char *)malloc(sizeof(itt->info.data));
	it->key2 = (char *)malloc(sizeof(itt->key2));
	it->key1 = itt->key1;
	puts("DD");
	it->info.one = itt->info.one;
	it->info.two = itt->info.two;
	strcpy(it->key2, itt->key2);
	strcpy(it->info.data, itt->info.data);
	return it;
}

void read_table(Table* table){
	for (int i = 0; i < table->size; i ++){
		if (!(table->ks1_size[i])) continue;
		Item* it = table->ks1[i].first;
		printf("%d\n", table->ks1_size[i]);
		for (int j = 0; j < table->ks1_size[i]; j ++){
			printf("\nElement with keys: %d and %s.\n", it->key1, it->key2);
			printf("Float numbers are %lf and %lf\n", it->info.one, it->info.two);
			printf("Your data is: %s\n", it->info.data);
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
	/*
	int i = 0, b = 0;
	for (; i < r; i++){
		if (table->ks1[hash].busy && table->ks1[hash].key ==  key) {
			b = 1;
			break;
		}
		
	}
	printf("%d\n", table->ks2_size[hash]);
	*/
	if (!table->ks1[hash].busy){
		printf("No item in table.\n");
		return ;
	}
	Item* it = table->ks1[hash].first;
	for (int i = 0; i < table->ks1_size[hash]; i ++){
		int hash2 = hash_1(*it->key2, r);
		while ( table->ks2[hash2].busy && *table->ks2[hash2].key != *table->ks2[hash2].key){
			hash2 = ((hash2 + hash_2(*it->key2, r)) % r);
		}
		Item* pit;
		puts("XX");
		//if (table->ks2[hash2].busy){
			Item* iit = table->ks2[hash2].first;
			pit = iit;
			int j = 0;
			for (; j < table->ks2_size[hash2] - 1; j ++){
				if (iit->key1 == it->key1) break;
				pit = iit;
				iit = iit->next;
			}
			puts("VV");
			if (j == 0 && table->ks2_size[hash2] > 1) 	table->ks2[hash2].first = pit->next;
			puts("SS");
			if (j + 1 < table->ks2_size[hash2] && table->ks2_size[hash2] > 2)
				pit->next = iit->next;
			puts("DD");
			if (table->ks2_size[hash2] == 1) table->ks2[hash2].busy = 0;
		//}
		puts("WW");
		pit = it->next;
		free(it->key2);
		free(it->info.data);
		free(it);
		it = NULL;
		puts("BB");
		table->ks1[hash].first = NULL;
		it = pit;
		pit = NULL;
		table->ks2_size[hash2] --;
		
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
	int hash = hash_1(*key, r);
	int i = 0, b = 0;
	while (table->ks2[hash].busy && *table->ks2[hash].key != *key){
		//printf("--%d\n", *table->ks2[hash].key);
		hash = ((hash + hash_2(*key, r)) % r);
	}
	/*
	for (; i < r; i++){
		if (table->ks2[hash].busy && !strcmp(table->ks2[hash].key, key)) {
			b = 1;
			break;
		}3

		hash = ((hash + hash_2((int)key, r)) % r);
	}
	puts("EE");*/
	printf("%d %d\n", table->ks2_size[hash], hash);
	if (!table->ks2[hash].busy){
		printf("No item in table.\n");
		return ;
	}
	Item* it = table->ks2[hash].first;
	Item* pit = it;
	for (int i = 0; i < table->ks2_size[hash]; i ++){
		int hash1 = hash_1(it->key1, r);
		while (table->ks1[hash1].busy && (table->ks1[hash1].key) != it->key1){
			hash1 = ((hash1 + hash_2(it->key1, r)) % r);
		}
		
		//if (table->ks1[hash1].busy){
			Item* iit = table->ks1[hash1].first;
			pit = iit;
			int j = 0;
			for (; j < table->ks1_size[hash1]; j ++){
				if (*iit->key2 == *it->key2) break;
				pit = iit;
				iit = iit->next;
			}
			if (j == 0 && table->ks1_size[hash1] > 1) table->ks1[hash1].first = pit->next;
			if (j + 1 < table->ks1_size[hash1] && table->ks1_size[hash1] > 2)
				pit->next = iit->next;
			
			if (table->ks1_size[hash1] == 1) table->ks1[hash1].busy = 0;
		//}
		pit = it->next;
		free(it->key2);
		free(it->info.data);
		free(it);
		it = NULL;
		
		it = pit;
		pit = NULL;
		table->ks1_size[hash1] --;
		
	}
	table->ks2[hash].first = NULL;
	table->ks2[hash].busy = 0;
	table->ks2_size[hash] = 0;
}

void delete_item_table(Table* table, int key1, char* key2){
	int r = table->size;
	int hash1 = hash_1(key1, r);
	int b = 0;
	while (table->ks1[hash1].busy && table->ks1[hash1].key != key1){
		hash1 = ((hash1 + hash_2(key1, r)) % r);
	}
	int hash2 = hash_1(*key2, r);
	while (table->ks2[hash2].busy && *table->ks2[hash2].key != *key2){
		hash2 = ((hash2 + hash_2(*key2, r)) % r);
	}

	if (!table->ks1[hash1].busy && !table->ks2[hash2].busy){
		printf("No item in table.\n");
		return ;
	}
	printf("%d\n", table->ks2_size[hash2]);
	Item* it1 = table->ks1[hash1].first;
	Item* it2 = table->ks2[hash2].first;
	Item* pit1 = it1;
	Item* pit2 = it2;
	int j = 0;
	for (; j < table->ks1_size[hash1] - 1; j ++){
		if (!strcmp(it1->key2,key2)) break;
			pit1 = it1;
			it1 = it1->next;
			pit1->next = it1;
	}
	int i = 0;
	for (; i < table->ks2_size[hash2] - 1; i ++){
		if (it2->key1 == key1) break;
			pit2 = it2;
			it2 = it2->next;
			pit2->next = it2;
	}
	if (j == 0 && table->ks1_size[hash1] > 1){
		table->ks1[hash1].first = pit1->next;
	}
	if (i == 0 && table->ks2_size[hash2] > 1){
		table->ks2[hash2].first = pit2->next;
	}
	if (j + 1 < table->ks1_size[hash1] && table->ks1_size[hash1] > 2)
		pit1->next = it1->next;
	if (i + 1 < table->ks2_size[hash2] && table->ks2_size[hash2] > 2){
		pit2->next = it2->next;
	}
	free(it1->key2);
	free(it1->info.data);
	free(it1);
	it1 = NULL;
	
	table->ks1_size[hash1] --;
	table->ks2_size[hash2] --;
}

void clear_table(Table* table){
	for (int i = 0; i < table->size; i ++){
		if (table->ks1_size[i]){
			Item* it = table->ks1[i].first;
			Item* pit;
			for (int j = 0; j < table->ks1_size[i]; j ++){
				pit = it->next;
				free(it->key2);
				free(it->info.data);
				free(it);
				it = pit;
			}
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
			if (j == 0){
				par_table->ks1[i].first = it;
				par_table->ks1[i].cur = it;
			}
			else{
				par_table->ks1[i].cur = it;
			}
			it = it->next;
		}
	}
	return par_table;
}