#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "kdtree.h"

Tree* create_t(){
	Tree* tree;
	create_tree(tree);
	return tree;
}

int info(){
	int g, n = 1;
	char* buf[] = {"\nChoose any  option.\n", "0) Insert info.\n", "1) Search for info.\n", "2) Delete info.\n", "3) Read tree.\n", "4) Remove tree.\n", "5) Search for neareast neighbour\n", "6) Leave...\n", "Your choice: "};
	do{
		if (n != 1) scanf("%*s");
		for (int i = 0; i < 9; i++){
			printf("%s", buf[i]);
		}
		n = scanf("%d%*c", &g);
	}while (g < 0 || g > 7 || n != 1);
	return g;
}

char* str_data(char* d){
	char* data = (char *)malloc(10 * sizeof(char));
	printf("%s", d);
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

int data_int(char* k){
	int n = 1, g;
	do{
		if (n != 1) scanf("%*s");
		printf("%s", k);
		n = scanf("%d%*c", &g);
	}while (g <= 0 || n != 1);
	return g;
}

void insert_t(Tree* tree){
	int x = data_int("Enter x coord: ");
	int y = data_int("Enter y coord: ");
	Node* node = tree->root;
	insert_tree(node);
}

void read_t(Tree* tree){
	int x1 = data_int("Enter first x range: ");
	int x2 = data_int("Enter second x range: ");;
	int y1 = data_int("Enter first y range:");
	int y2 = data_int("Enter second y range: ");
	read_tree(tree->root, x1, x2, y1, y2);
}

void clear_t(Tree* tree){

}

void delete_t(Tree* tree){

}

void search_n_t(Tree* tree){

}

void search_t(Tree* tree){

}