#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"

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

Deque* create_deque(){
    Deque *deque = (Deque *)calloc(1, sizeof(Deque));
    deque->size = 0;
    deque->head = deque->tail = NULL;
    return deque;
}

void delete_deque(Deque **deque) {
    Node *node = (*deque)->head;
    Node *next = NULL;
    while (node) {
        next = node->next;
		free(node->value);
        free(node);
        node = next;
    }
    free(*deque);
    (*deque) = NULL;
}

void push_front(Deque *deque) {
    Node *node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {
        return ;
    }
    node->value = str_data("Enter data: ");
    node->next = deque->head;
    node->prev = NULL;
    if (deque->head) {
        deque->head->prev = node;
    }
    deque->head = node;
 
    if (deque->tail == NULL) {
        deque->tail = node;
    }
    deque->size++;
}

void pop_front(Deque *deque) {
    Node *prev;
    char* val;
    if (deque->head == NULL) {
        return ;
    }
    prev = deque->head;
    deque->head = deque->head->next;
    if (deque->head) {
        deque->head->prev = NULL;
    }
    if (prev == deque->tail) {
        deque->tail = NULL;
    }
    val = prev->value;
	free(val);
    free(prev);
 
    deque->size--;
}


void push_back(Deque *deque) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node == NULL) {
        return ;
    }
    node->value = str_data("Enter data: ");
    node->next = NULL;
    node->prev = deque->tail;
    if (deque->tail) {
        deque->tail->next = node;
    }
    deque->tail = node;
 
    if (deque->head == NULL) {
        deque->head = node;
    }
    deque->size++;
}
 
void pop_back(Deque *deque) {
    Node *next;
    char* val;
    if (deque->tail == NULL) {
        return ;
    }
 
    next = deque->tail;
    deque->tail = deque->tail->prev;
    if (deque->tail) {
        deque->tail->next = NULL;
    }
    if (next == deque->head) {
        deque->head = NULL;
    }
    val = next->value;
	free(val);
    free(next);
 
    deque->size--;
}

void read_deque_front(Deque* deque){
	Node* node = deque->head;
	int i = 1;
	while(node){
		printf("\nNode number %d.\n", i);
		printf("Data: %s\n", node->value);
		node = node->next;
		i++;
	}
}

void read_deque_back(Deque* deque){
	Node* node = deque->tail;
	int i = deque->size;
	while(node){
		printf("\nNode number %d.\n", i);
		printf("Data: %s\n", node->value);
		node = node->prev;
		i--;
	} 
}