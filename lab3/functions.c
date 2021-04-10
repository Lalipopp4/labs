#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "table.h"
#include "functions.h"

int check_table(Table** table){
	if(*table){
		return 1;
	}
	else{
		printf("Error! No table found in memory.\n");
		return 0;
	}
}

void delete_table(Table** table){
	if(check_table(table) != 0)
		clear_table(*table);
}

void T_clear(Table** table){
	if (check_table(table) != 0){
		clear_table(*table);
		*table = NULL;
	}
}

char* str_data(char d[]){
	printf("%s", d);
	char* data = NULL;
	char c;
	int i = 0;
	scanf("%c", &c);
	while (c != '\n'){
		if (i % 10 == 0) data = realloc(data, (i + 10) * sizeof(char));
		data[i] = c;
		scanf("%c", &c);
		i++;
	}
	return data;
}
	

int data_int(char* k){
	int n = 1, g;
	do{
		if (n != 1) scanf("%*s");
		printf("%s", k);
		n = scanf("%d%*c", &g);
	}while (g <= 0 || n != 1);
	return g;
}

void T_delete(Table** table){
	int g, n = 1;
	do{	
		printf("Choose any option:\n");
		printf("1) KS1 key.\n");
		printf("2) KS2 key.\n");
		printf("3) Both keys.\n");
		printf("Your choice: ");
		scanf("%d", &g);
	}while(g <= 0 || g >= 4 || n != 1);
	if (g == 1){
		int key = data_int("Enter your key: ");
		ks1_delete_item_table(*table, key);
	}
	else if (g == 2){
		char* key = str_data("Enter your key: ");
		ks2_delete_item_table(*table, key);
		free(key);
	}
	else{
		int key1 = data_int("Enter first key: ");
		char* key2 = str_data("Enter second key: ");
		delete_item_table(*table, key1, key2);
		free(key2);
	}
}

void T_read(Table** table){
	if (check_table(table) != 0){
		read_table(*table);
	}
}

void T_insert(Table** table){
	if (check_table(table) != 0){
		insert_table(*table);
	}
}

void T_search(Table** table){
	if (check_table(table) != 0){
	int g, n = 1;
	char* f;
	do{
		if (n != 1)scanf("%*s");
		printf("What do you want to use?\n");
		printf("1) Int key.\n");
		printf("2) Char key.\n");
		printf("3) Composite key.\n");
		printf("Your choice: ");
		n = scanf("%d%*c", &g);
	}while (g <= 0 || g >= 4 || n != 1);
	Item* it = NULL;
	if (g == 1){
		int g = data_int("Enter your key: ");
		it = ks1_search_table(*table, g);
		int i = 0;
		while(it){
			printf("\nElement with keys: %d and %s.\n", it[i].key1, it[i].key2);
			printf("Float numbers are %lf and %lf.\n", it[i].info->one, it[i].info->two);
			printf("Your data is: %s.\n", it[i].info->data);
			it = it->next;
		}
	}
	else if (g == 2){
		char* g = str_data("Enter your key: ");
		it = ks2_search_table(*table, g);
		int i = 0;
		while(it){
			printf("\nElement with keys: %d and %s.\n", it[i].key1, it[i].key2);
			printf("Float numbers are %lf and %lf.\n", it[i].info->one, it[i].info->two);
			printf("Your data is: %s.\n", it[i].info->data);
			it = it->next;
		}
		free(g);
	}
	else{
		int g = data_int("Enter first key: ");
		char* g2 = str_data("Enter second key: ");
		it = search_table(*table, g, g2);
		printf("\nElement with keys: %d and %s.\n", it->key1, it->key2);
		printf("Float numbers are %lf and %lf.\n", it->info->one, it->info->two);
		printf("Your data is: %s.\n", it->info->data);
		free(g2);
	}
	}
}
void T_create(Table** table){
	if(*table){
		printf("No need in creating a table, it is already created.\n");
	}
	else{
		int n = data_int("Enter size of table: ");
		*table = create_table(n);
		printf("Table was successfully created.\n");
	}
}

void T_par_table(Table** table){
	if (check_table(table) != 0){
	Table** par_table = NULL;
	*par_table = parent_table(*table, *par_table);
	double n,m;
	for (int i = 0; i < (*table)->size; i ++){
		if (!(*par_table)->ks1_size) continue;
		Item* it = (*par_table)->ks1[i].first;
		printf("Key: %d.\n", (*par_table)->ks1[i].key);
		for (int j = 0; j < (*par_table)->ks1_size[i]; j ++){
			n = it->info->one;
			m = it->info->two;
			printf("Element with keys: %d and %s.\n", (*par_table)->ks1[i].key, (*par_table)->ks1[i].item->key2);
			printf("Float numbers are %lf and %lf.\n", n, m);
			printf("Your data is: %s.\n", it->info->data);
			printf("Parent key is %d.\n", (*par_table)->ks1[i].par);
		}
	}
	clear_table(*par_table);
	}
}

int inform(){	
	int g, n = 1;
	do{
		if (n != 1) scanf("%*s");
		printf("\nChoose any  option.\n");
		printf("0) Create table.\n");
		printf("1) Insert info.\n");
		printf("2) Search for info.\n");
		printf("3) Delete info.\n");
		printf("4) Read table.\n");
		printf("5) Remove table.\n");
		printf("6) Make new table with child elements.\n");
		printf("7) Leave...\n");
		printf("Your choice: ");
		n = scanf("%d%*c", &g);
	}while (g < 0 || g > 7 || n != 1);
	return g;
}