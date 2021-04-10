#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"

Table* create_table(){
	char file[80];
	printf("Enter name of binary file: ");
	scanf("%s%*c", file);
	FILE* f = fopen(file, "rb");
	Table* table = calloc(1, sizeof(Table));
	fread(&table->size, sizeof(int), 1, f);
	table->file = file;
	table->ks1_size = (int *)malloc(table->size * sizeof(int));
	table->ks2_size = (int *)malloc(table->size * sizeof(int));
	for (int i= 0; i < table->size; i ++){
		table->ks1_size[i] = 0;
		table->ks2_size[i] = 0;
	}
	table->pos = 0;
	KS1* ks1;
	ks1 = (KS1 *)malloc(table->size * sizeof(KS1));
	table->ks1 = ks1;
	KS2* ks2;
	ks2 = (KS2 *)malloc(table->size * sizeof(KS2));
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

void insert_table(Table* table, int key1, char* key2){
	FILE* f = fopen(table->file, "rb");
	double n,m;
	char str[80];
	printf("Enter two float numbers: ");
	scanf("%lf %lf%*c", &n, &m); 
	printf("Enter string data: ");
	scanf("%s%*c", str);
	int r = table->size;
	int hash1 = hash1 = hash_1(key1, r);
	while (table->ks1[hash1].key != key1){
		hash1 = ((hash1 + hash_2(key1, r))  % table->size);
	}
	int hash2 = hash_1((int)key2, r);
	while (table->ks2[hash2].key != key2){
		hash2 = ((hash2 + hash_2((int)key2, r)) % table->size);
	}
	Item* it = (Item *)malloc(sizeof(Item));
	table->ks1_size[hash1]++;
	table->ks2_size[hash2]++;
	if (table->ks1_size[hash1] == 1) table->ks1[hash1].first = it;
	if (table->ks2_size[hash2] == 1) table->ks2[hash2].first = it;
	int g = sizeof(key1) + sizeof(key2) + sizeof(double) * 2 + sizeof(str);
	int t = sizeof(key2);
	fwrite(&key1, sizeof(int), 1, f);
	fwrite(&t, sizeof(int), 1, f);
	fwrite(key2, sizeof(key2), 1, f);
	fwrite(&n, sizeof(double), 1, f);
	fwrite(&m, sizeof(double), 1, f);
	fwrite(str, sizeof(char), strlen(str), f);
	table->ks1[hash1].busy = 1;
	table->ks2[hash2].busy = 1;
	it->pos = table->pos;
	it->size = g;
	int u, y = 1, b = 0;
	do{
			if (y != 1) scanf("%*s");
			printf("If this key has a parent, write it or 0 if not.\n");
			printf("Your choice: ");
			n = scanf("%d%*c", &u);
			for (int j = 0; j < table->size; j ++){
				if (table->ks1[j].key && table->ks1[j].key == g){
					b = 1;
				}
			}
	}while(y != 1);
	if (b == 1)
			table->ks1[hash1].par = u;
	else
			printf("No items with this key.\n");
	it->k2size = sizeof(key2);
	table->pos += g;
	it = it->next;
}

Item_c* ks1_search_table(Table* table, int key){
	FILE* f = fopen(table->file, "rb");
	int r = table->size;
	int hash = hash_1(key, r);
	while (table->ks1[hash].busy && table->ks1[hash].key != key){
		hash = ((hash + hash_2(key, r)) % r);
	}
	int i = 0;
	if (!table->ks1_size[hash]) return NULL;
	printf("Key: %d\n", key);
	Item* it = table->ks1[hash].first;
	Item_c* it_copy = (Item_c *)malloc(table->ks1_size[hash] * sizeof(Item_c));
	for (int i = 0; i < table->ks1_size[i]; i ++){
		fseek(f, it->pos, 0);
		it_copy[i].info = (Info *)malloc(sizeof(Info));
		it_copy[i].info->data = (char *)malloc(80);
		fread(&it_copy[i].key1, sizeof(int), 1, f);
		fread(&it_copy[i].key2, it->k2size, 1, f);
		fread(&it_copy[i].info->one, sizeof(double), 1, f);
		fread(&it_copy[i].info->two, sizeof(double), 1, f);
		fread(&it_copy[i].info->data, 80, 1, f);
		it = it->next;
	}
	return it_copy;
}

Item_c* ks2_search_table(Table* table, char* key){
	FILE* f = fopen(table->file, "rb");
	int r = table->size;
	int hash = hash_1((int)key, r);
	while (table->ks2[hash].busy && (int)table->ks2[hash].key != (int)key){
		hash = ((hash + hash_2((int)key, r)) % r);
	}
	int i = 0;
	if (!table->ks2_size[hash]) return NULL;
	printf("Key: %s\n", key);
	Item* it = table->ks2[hash].first;
	Item_c* it_copy = (Item_c *)malloc(table->ks2_size[hash] * sizeof(Item_c));
	for (int i = 0; i < table->ks2_size[i]; i ++){
		fseek(f, it->pos, 0);
		it_copy[i].info = (Info *)malloc(sizeof(Info));
		it_copy[i].info->data = (char *)malloc(80);
		fread(&it_copy[i].key1, sizeof(int), 1, f);
		fread(&it_copy[i].key2, it->k2size, 1, f);
		fread(&it_copy[i].info->one, sizeof(double), 1, f);
		fread(&it_copy[i].info->two, sizeof(double), 1, f);
		fread(&it_copy[i].info->data, sizeof(char), 1, f);
		it = it->next;
	}
	return it_copy;
}

void search_table(Table* table, int key1, char* key2){
	double n, m;
	char key[80];
	char str[80];
	FILE* f = fopen(table->file, "rb");
	int r = table->size;
	int hash1 = hash_1(key1, r);
	while (table->ks1[hash1].key != key1){
		hash1 = ((hash1 + hash_2(key1, r)) % r);
	}
	Item* it = table->ks1[hash1].first;
	{
		fseek(f, it->pos + 8, 0);
		fread(&key, it->k2size, 1, f);
		it = it->next;
	}while ((int)key != (int)key2);
	fread(&n, sizeof(double), 1, f);
	fread(&m, sizeof(double), 1, f);
	fread(&str, 80, 1, f);
	printf("\nElement with keys: %d and %s.\n", key1, key2);
	printf("Float numbers are %lf and %lf.\n", n, m);
	printf("Your data is: %s\n", str);
}

void read_table(Table* table){
	FILE* f = fopen(table->file, "rb");
	double n,m;
	int key1, h;
	char str[80];
	char key2[80];
	for (int i = 0; i < table->size; i ++){
		fread(&key1, sizeof(int), 1, f);
		fread(&h, sizeof(int), 1, f);
		fread(&key2, h, 1, f);
		fread(&n, sizeof(double), 1 , f);
		fread(&m, sizeof(double), 1 ,f);
		fread(&str, 80, 1, f);
		printf("Keys are: %d and %s.\n", key1, key2);
		printf("Float numbers are: %lf and %lf.\n", n, m);
		printf("Data: %s\n", str);
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
	char* key2 = (char *)malloc(it->k2size);
	char* kk;
	
	for (int i = 0; i < table->ks1_size[hash]; i ++){
		fseek(f, it->pos + 8, 0);
		fread(&key2, it->l2size, 1, f);
		int hash2 = hash_1((int)key2, r);
		while (table->ks1[hash].busy && (int)table->ks2[hash].key != (int)key2){
			hash2 = ((hash + hash_2((int)key2, r)) % r);
		}
		Item* iit = table->ks2[hash2].first;
		Item* pit;
		int j = 0;
		do{
			fseek(f, iit->pos + 8, 0);
			kk = (char *)malloc(iit->l2size);
			fread(&kk, iit->k2size, 1, f);
			pit = iit;
			iit = iit->next;
			j++;
		}while ((int)kk != (int)key2);
		if (j < table->ks2_size[hash2])
			pit->next = iit->next;
		free(it);
		it->busy = 0;
		it = it->next;
		table->ks2_size[hash2] --;
		if (table->ks2_size[hash2] == 0) table->ks2[hash2].busy = 0;
	}
	table->ks1[hash].first = NULL;
	//free(it);
	for (int i = 0; i < table->size; i ++){
		if (table->ks1[hash].par == key)
			table->ks1[hash].par = 0;
	}
	table->ks1[hash].busy = 0;
	table->ks1_size[hash] = 0;
}

void ks2_delete_item_table(Table* table, char* key){
	int r = table->size;
	FILE* f = fopen(table->file, "rb");
	int hash = hash_1((int)key, r);
	while (table->ks2[hash].busy && (int)table->ks2[hash].key != (int)key){
		hash = ((hash + hash_2((int)key, r)) % r);
	}
	if (!(table->ks2[hash].busy)){
		printf("No item in table.\n");
		return ;
	}
	Item* it = table->ks2[hash].first;
	char* key2 = (char *)malloc(it->k2size);
	char* kk;
	
	for (int i = 0; i < table->ks2_size[hash]; i ++){
		fseek(f, it->pos + 8, 0);
		fread(&key2, it->l2size, 1, f);
		int hash2 = hash_1((int)key2, r);
		while (table->ks1[hash].busy && (int)table->ks2[hash].key != (int)key2){
			hash2 = ((hash + hash_2((int)key2, r)) % r);
		}
		Item* iit = table->ks2[hash2].first;
		Item* pit;
		int j = 0;
		do{
			fseek(f, iit->pos + 8, 0);
			kk = (char *)malloc(iit->l2size);
			fread(&kk, iit->k2size, 1, f);
			pit = iit;
			iit = iit->next;
			j++;
		}while ((int)kk != (int)key2);
		if (j < table->ks2_size[hash2])
			pit->next = iit->next;
		free(it);
		it->busy = 0;
		it = it->next;
		table->ks2_size[hash2] --;
		if (table->ks2_size[hash2] == 0) table->ks2[hash2].busy = 0;
	}
	table->ks1[hash].first = NULL;
	//free(it);
	for (int i = 0; i < table->size; i ++){
		if (table->ks1[hash].par == key)
			table->ks1[hash].par = 0;
	}
	table->ks1[hash].busy = 0;
	table->ks1_size[hash] = 0;
}

void delete_item_table(Table* table, int key1, char* key2){
	int 
	int hash1 = hash_1(key1);
	while (table->ks1[hash1].key != key1){
		hash1 += hash_2(key1);
	}
	int hash2 = hash_1((int)key2);
	while (table->ks2[hash2].key != key2){
		hash2 += hash_2((int)key2);
	}
	int k = 0, m = 0;
	Item* it1 = table->ks1[hash1].first;
	Item* it2 = table->ks1[hash2].first;
	Item* pit1;
	Item* pit2;
	while (it1->key1 != key1){
		pit1 = it1;
		it1 = it1->next;
		k++;
	}
	while (it2->key2 != key2){
		pit2 = it2;
		it2 = it2->next;
		m++;
	}
	if (it1->next){
		pit1->next = it1->next;
	}
	free(it1->info);
	free(it1);
	it1 = NULL;
	if (it2->next){
		pit2->next = it2->next;
	}
	it2 = NULL;
}

void clear_table(Table* table){
	for (int i = 0; i < table->size; i ++){
		if (!table->ks1_size[i]) continue;
		Item* it = table->ks1[i].first;
		for (int j = 0; j < table->ks1_size[i]; j ++){
			free(it);
			it = it->next;
		}
	}
	free(table->ks1_size);
	free(table->ks2_size);
	free(table->ks1);
	free(table->ks2);
	free(table);
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