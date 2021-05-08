#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "kdtree.h"

Tree* create_tree(Tree* tree){
	tree = (Tree *)malloc(sizeof(Tree *));
	tree->root = NULL;
	tree->n = data_int("Enter N: ");
	tree->file = str_data("Enter file name: ");
}

void insert_tree(Node* node){
	int i = 0;
	int n = data_int("Keyboard input (1) or file (1>): ");
	char* data = NULL;
	float num;
	//int n = 1;
	if (n == 1){
		int x = data_int("Enter x coord: ");
		int y = data_int("Enter y coord: ");
		data = str_data("Enter data: ");
		
	}
	else{
		int s1, s2;
		FILE* f = fopen(tree->file, "rb");
		if (f){
		fread(&key, sizeof(unsigned int), 1, f);
		fread(&s1, sizeof(int), 1, f);
		fread(one, s1, 1, f);
		fread(&s2, sizeof(int), 1, f);
		fread(two, s2, 1, f);}
		else{
			printf("No file in memory.\n");
			return ;
		}

	}
	if (!node)
	while (node){
		if (i % 2 == 0){
			if (x < node->key[0])
				node = node->left;
			else if (x > node->key[1])
				node = node->right;
			else
				insert_info(node);
				return ;
		}
		else{
			if (y < node->key[0])
				node = node->left;
			else if (y > node->key[1])
				node = node->right;
			else
				insert_info(node);
				return ;
		}
		insert_info(node);
	}
}

void clear_node(Node* node){
	if (node){
		clear_node(node->left);
		clear_node(node->right);
		if (node->item){
			Item* it = node->item;
			Item* n = NULL;
			while(it){
				n = it->next;
				free(it->data);
				free(it);
				it = n;
			}
		}
		free(node);
	}
}

Tree* clear_tree(Tree* tree){
	clear_node(tree->root);
	free(tree->file);
	free(tree);
	return NULL;
}

void read_tree(Node* node, int x1, int x2, int y1, int y2){
	if (node) read_tree(node->right, x1, x2, y1, y2);
	if (node->item && node->key[0] < x2 && node->key[0] > x1 && node->key[1] < y2 && node->key[0] > y1){
		printf("Coords are: %d and %d\n", node->key[0], node->key[1]);
		Item* it = node->item;
		while (it){
			printf("Float number is: %lf\n", it->num);
			printf("Data: %s\n", it->data);
			it = it->next;
			printf("\n");
		}
	}
	read_tree(node->left, x1, x2, y1, y2);
}