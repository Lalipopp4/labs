#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tree.h"
#include "functions.h"

int check_tree(Tree** tree){
	if (*tree){
		return 1;
	}
	else{
		printf("No tree in memory.\n");
		return 0;
	}
}

char* str_data(char d[]){
	printf("%s", d);
	char buf[20] = {0};
	char* res = NULL;
	int len = 0;
	int n = 0;
	do{
		n = scanf("%20[^\n]",buf);
		if(n < 0){
			if(!res) return NULL;	
		} else if(n > 0){
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res,str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		} else{
			scanf("%*c");
		}
	}while(n > 0);

	if(len > 0) res[len] = '\0';
	else res = calloc(1,sizeof(char));
	return res;
}

unsigned int int_data(char* k){
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
	clock_t t1 = clock();
	insert_tree(*tree);
	clock_t t2 = clock();
	printf("Time to insert: %f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}

void read_t(Tree** tree){
	Node* node = (*tree)->root;
	int key = int_data("Enter max key: ");
	clock_t t1 = clock();
	read_tree(node, key);
	clock_t t2 = clock();
	printf("Time to read: %f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}

void search_t(Tree** tree){
	int key = int_data("Enter your key: ");
	Node* node = (*tree)->root;
	Item* it;
	clock_t t1 = clock();
	while (node){
		if (key > node->key){
			node = node->right;
		}
		else if(key < node->key){
			node = node->left;
		}
		else{
			printf("Key is: %d.\n", key);
			it = search_tree(node);
			break;
		}
	}
	if (!node) printf("No node with this key.\n");
	else{
		printf("First string: %s\n", it->one);
		printf("Second string: %s\n", it->two);
	}
	clock_t t2 = clock();
	printf("Time to search: %f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}

void search_n_t(Tree** tree){
	int key = int_data("Enter your key: ");
	int n = 100000;
	int *qn = &n;
	Item* it;
	clock_t t1 = clock();
	search_near_key_tree((*tree)->root, key, qn, it);
	int h = 1;
	if (it->next)
		h = int_data("Enter number of item: ");
	for (int i = 0; i < n - 1; i ++){
		it = it->next;
	}
	printf("Key: %d.\n", key);
	printf("Difference between keys is %d.\n", *qn);
	printf("First string: %s\n", it->one);
	printf("Second string: %s\n", it->two);
	clock_t t2 = clock();
	printf("Time to search nearest: %f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}

void delete_t(Tree** tree){
	int key = int_data("Enter your key: ");
	Node* node = (*tree)->root;
	clock_t t1 = clock();
	delete_node(*tree, node, key);
	printf("%d\n", (*tree)->root->key);
	clock_t t2 = clock();
	printf("Time to search delete node: %f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}

void clear_t(Tree** tree){
	if (check_tree(tree) == 1)
	clear_tree(*tree);
}

void create_t(Tree** tree){
	if(*tree){
		printf("No need in creating a tree, it is already created.\n");
	}
	else{
		*tree = create_tree();
		printf("Tree was successfully created.\n");
	}
}

int info(){
	int g, n = 1;
	do{
		if (n != 1) scanf("%*s");
		printf("\nChoose any  option.\n");
		printf("0) Create tree.\n");
		printf("1) Insert info.\n");
		printf("2) Search for info.\n");
		printf("3) Search for nearest key.\n");
		printf("4) Delete info.\n");
		printf("5) Read tree.\n");
		printf("6) Remove tree.\n");
		printf("7) Leave...\n");
		printf("Your choice: ");
		n = scanf("%d%*c", &g);
	}while (g < 0 || g > 7 || n != 1);
	return g;
}