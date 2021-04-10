#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "functions.h"

int check_tree(Tree** tree){
	if (tree){
		return 1;
	}
	else{
		printf("No tree in memory.\n");
		return 0;
	}
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

unsigned int data_int(char* k){
	int n = 1, g;
	do{
		if (n != 1) scanf("%*s");
		printf("%s", k);
		n = scanf("%d%*c", &g);
	}while (g <= 0 || n != 1);
	return g;
}

void insert_t(Tree** tree){
	if (check_tree(tree) == 0) return ;
	unsigned int key = data_int("Enter your key: ");
	Node* node = (*tree)->root;
	if (!node->key){
		insert_tree(node, NULL, key);
		return ;
	} 
	Node* node1;
	while (1){
		if (key > node->key){
			node1 = node;
			node = node->right;
			if (!node->right){
				insert_tree(node, node1, key);
				break;
			}
		}
		else if(key < node->key){
			node1 = node;
			node = node->left;
			if (!node-> left){
				insert_tree(node, node1, key);
				break;
			}
		}
		else{
			insert_tree(node, NULL, key);
			break;
		}
		node->root = (*tree)->root;
	}
}

void read_t(Tree** tree){
	Node* node = (*tree)->root;
	read_tree(node);
}

void search_t(Tree** tree){
	int key = data_int("Enter your key: ");
	Node* node = (*tree)->root;
	while (node){
		if (key > node->key){
				node = node->right;
		}
		else if(key < node->key){
			node = node->left;
		}
		else{
			printf("Key is: %d.\n", key);
			search_tree(node, key);
			break;
		}
	}
	if (!node) printf("No node with this key.\n");
}

void search_near_key(Tree** tree){
	int key = data_int("Enter your key: ");
	int n = 100000;
	int *qn = &n;
	Item* it;
	search_near_key_tree((*tree)->root, key, qn, it);
	printf("Key: %d.\n", key);
	printf("Difference between keys is %d.\n", *qn);
	printf("First string: %s\n", it->one);
	printf("Second string: %s\n", it->two);

}

int info(){
	int g, n = 1;
	do{
		if (n != 1) scanf("%*s");
		printf("\nChoose any  option.\n");
		printf("0) Insert info.\n");
		printf("1) Search for info.\n");
		printf("2) Delete info.\n");
		printf("3) Read tree.\n");
		printf("4) Remove tree.\n");
		printf("5) Leave...\n");
		printf("Your choice: ");
		n = scanf("%d%*c", &g);
	}while (g < 0 || g > 7 || n != 1);
	return g;
}