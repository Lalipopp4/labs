#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tree.h"
#include "functions.h"

Tree* create_tree(){
	Tree* tree = (Tree *)calloc(1, sizeof(Tree));
	tree->file = str_data("Enter name of input file: ");
	tree->root = NULL;
	return tree;
}

void insert_tree(Tree* tree){
	int n = int_data("Keyboard input (1) or file (1>): ");
	unsigned int key;
	char* one = NULL;
	char* two = NULL;
	//int n = 1;
	if (n == 1){
		key = int_data("Enter your key: ");
		one = str_data("Enter first string: ");
		two = str_data("Enter second string: ");
	}
	else{
		int s1, s2;
		FILE* f = fopen(tree->file, "rb");
		fread(&key, sizeof(unsigned int), 1, f);
		fread(&s1, sizeof(int), 1, f);
		fread(one, s1, 1, f);
		fread(&s2, sizeof(int), 1, f);
		fread(two, s2, 1, f);
	}
	Node* node = tree->root;
	Node* prev = NULL;
	Node* next = NULL;
	int h = 0;
	while (node){
		h = 1;
		if (key > node->key){
			prev = node;
			node = node->right;
			h = 2;
		}
		else if(key < node->key){
			next = node;
			node = node->left;
			next->left = node;
			h = 3;
		}
		else{
			Item* it = node->first;
			while(it->next){
				it = it->next;
			}
			it->next = (Item *)malloc(sizeof(Item));
			it = it->next;
			it->one = one;
			it->two = two;
			return ;
		}
		if (!node){
			break;
		}
		
	}
	node = (Node *)malloc(sizeof(Node));
	node->key = key;
	node->first = (Item *)malloc(sizeof(Item));
	node->first->one = one;
	node->first->two = two;
	node->first->next = NULL;
	node->left = NULL;
	node->right = NULL;
	node->root = tree->root;
	node->next = next;
	node->prev = prev;
	if (h == 2) prev->right = node;
	if (h == 3)next->left = node;
	if (prev) prev->next = node;
	if (next) next->prev = node;
	if (h == 0) tree->root = node;
}

void read_tree(Node* node, int key){
	if (node && node->key <= key){
		read_tree(node->left, key);
		printf("   Key is %d\n", node->key);
		Item* it = node->first;
		while (it){
			printf("First string: %s\n", it->one);
			printf("Second string: %s\n", it->two);
			it = it->next;
			printf("\n");
		}
		read_tree(node->right, key);
		
	}
}

Item* search_tree(Node* node){
	Item* it = node->first;
	int n = 1, j = 0;
	if (it->next)
		n = int_data("Enter number of item: ");
	for (int i = 0; i < n - 1; i ++){
		it = it->next;
	}
	return it;
}

void clear_node(Node* node){
	if (node){
		clear_node(node->left);
		clear_node(node->right);
		Item* it = node->first;
		Item* n = NULL;
		while(it){
			n = it->next;
			free(it->one);
			free(it->two);
			free(it);
			it = n;
		}
		free(node);
	}
}

void clear_tree(Tree* tree){
	clear_node(tree->root);
	free(tree);
}

void search_near_key_tree(Node* node, int key, int *qn, Item* it){
	if (node && pow(node->key - key, 2) < *qn){
		if ( pow(node->key - key, 2) < *qn){
			*qn = pow(node->key - key, 2);
			it = node->first;
		}
		search_near_key_tree(node->right, key, qn, it);
		search_near_key_tree(node->left, key, qn, it);
	}
}

Node * minValueNode(Node* node){
	Node* cur = node;
	while (cur->left) cur = cur->left;
	return cur;
}

Node* delete_node(Tree* tree, Node* node, int key){
	if (!node) return node;
	if (key < node->key) node->left = delete_node(tree, node->left, key);
	else if (key > node->key) node->right = delete_node(tree, node->right, key);
	else{
		if (!node->left){
			Node *temp = node->right;
			Item* it = node->first;
			Item* iit = NULL;
			int n = 1, i = 0;
			if (it->next)
				n = int_data("Enter number of item: ");
			for (i = 0; i < n - 1; i ++){
				iit = it;
				it = it->next;
			}
			if (n > 1){
				if (i == 0) node->first = it->next;
				iit->next = it->next;
				free(it);
			}
			else {
				tree->size--;
				if (tree->size == 1)
				tree->root = temp;
				free(node->first->one);
				free(node->first->two);
				free(node);
			}
			return temp;
		}
		else if (!node->right){
			Node *temp = node->left;
			Item* it = node->first;
			int n = 1, i = 0;
			if (it->next)
				n = int_data("Enter number of item: ");
			Item* iit = NULL;
			for (i = 0; i < n - 1; i ++){
				iit = it;
				it = it->next;
			}
			if (n > 1){
				if (i == 0) node->first = it->next;
				iit->next = it->next;
				free(it);
			}
			else {
				tree->size--;
				if (tree->size == 1)
				tree->root = temp;
				free(node->first->one);
				free(node->first->two);
				free(node);
			}
			return temp;
		}
		Node* temp = minValueNode(node->right);
		node->key = temp->key;
		node->right = delete_node(tree, node->right, temp->key);
	}
	return node;
}