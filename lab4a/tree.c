#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tree.h"
#include "functions.h"

Tree* create_tree(Tree* tree){
	tree = (Tree *)calloc(1, sizeof(Tree));
	return tree;
}

void insert_tree(Node* node, Node* prev_node, int key){
	node = (Node *)malloc(sizeof(Node));
	node->key = key;
	node->item = (Item *)malloc(sizeof(Item));
	node->item->one = str_data("Enter first string: ");
	node->item->two = str_data("Enter second string: ");
	if (!node->first) node->first = node->item;
	node->left = NULL;
	node->right = NULL;
	if (prev_node){
		node->prev = prev_node; 
	}
	Item* g = node->item;
	node->item->next = NULL;
	node->item = node->item->next;
	g->next = node->item;
}

void read_tree(Node* node){
	if (node){
		printf("Key is: %d.\n", node->key);
		Item* it = node->first;
		while (it){
			printf("First string: %s\n", it->one);
			printf("Second string: %s\n", it->two);
			it = it->next;
			printf("\n");
		}
		read_tree(node->right);
		read_tree(node->right);
	}
}

void search_tree(Node* node){
	Item* it = node->first;
	int n = 1, j = 0;
	if (it->next)
		n = data_int("Enter number of item: ");
	for (int i = 0; i < n - 1; i ++){
		it = it->next;
	}
	printf("First string: %s\n", it->one);
	printf("Second string: %s\n", it->two);
}

void delete_tree(Node* node){
	Item* it = node->first;
	Node* node_l = node->left;
	Item* iit;
	int n = 1, j = 0;
	if (it->next)
		n = data_int("Enter number of item: ");
	for (int i = 0; i < n - 1; i ++){
		iit = it;
		it = it->next;
	}
	if (n == 1){
		node->first = 
	}

}

void search_near_key_tree(Node* node, int key, int *qn, Item* it){
	if (node){
		if ( pow(node->key - key, 2) < *qn){
			*qn = pow(node->key - key, 2);
			it = node->item;
		}
		search_near_key_tree(node->right, key, *qn, it);
		search_near_key_tree(node->right, key, *qn, it);
	}
}