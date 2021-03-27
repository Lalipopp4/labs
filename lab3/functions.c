#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "table.h"
#include "functions.h"

int check_table(Table* table){
	if(!table){
		printf("Error! No table found in memory.\n");
		return 0;
	}
	else return 1;
}
void delete_table(Table** table){
	if(*table) clear_table(*table);
}
int T_clear(Table* table){
	if (check_table(table) == 0) return 0;
	clear_table(table);
	table = NULL;
	return 0;
}

char* str_data(char* d){
	char* data = (char *)malloc(10 * sizeof(char));
	printf("Enter %s: ", d);
	int i = 0;
	char c;
	scanf("%c", &c);
	while(c != '\n'){
		data[i] = c;
		i++;
		if (i % 10 == 0) data = (char *)realloc(data, i * sizeof(char));
		scanf("%c", &c);
	}
	return data;
}

void T_delete(Table* table){
	
}

int T_read(Table* table){
	if (check_table(table) == 0) return 0;
	read_table(*table);
	return 0;
}

int T_insert(Table* table){
	int k1, a, i = 0;
	char* k2 = str_data("second key");
	Info info;
	if (check_table(table) == 0) return 0;
	printf("Enter first key: ");
	while (!scanf("%d%*c", &k1)){
		printf("Repeat input.\n");
		printf("Enter first key: ");
	}
	info.data = str_data("info");
	insert_table(table, k1, k2, info);
	free(k2);
	//free(info.data);
	return 0;
}

int T_search(Table* table){

}
int T_create(Table** table){
	if(*table){
		printf("No need in creating a table, it is already created.\n");
		return 0;
	}
	int n;
	printf("Enter size of table: ");
	while (scanf("%d%*c", &n)){
		printf("Invalid input.\n");
		printf("Enter size of table: ");
	}
	*table = create_table(n);
	printf("Table was successfully created.\n");
	return 0;
}

int inform(){	
	int g;
	do{
		printf("Choose any  option.\n");
		printf("0) Create table.\n");
		printf("1) Insert info.\n");
		printf("2) Search for info.\n");
		printf("3) Delete info.\n");
		printf("4) Read table.\n");
		printf("5) Remove table.\n");
		printf("6) Leave...\n");
		printf("Your choice: ");
		scanf("%d%*c", &g);
	}while (g >= 0 && g <= 6);
	return g;
}