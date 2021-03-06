#include "s2_l2_struct.h"

#include <stdio.h>
#include <malloc.h>


int push_struct(pas* a){
	printf("Enter id/ta/ts.\n");
	char c;
	int i = 0;
	scanf("%c", &c);
	while (c != '/'){
		a->id[i] = c;
		i++;
		scanf("%c", &c);
	}
	/*
	int u;
	do{
		u = scanf("%d", &i);

	}while ()*/
	scanf("%d", &a->ta);
	scanf("%d", &i);
	a->ts = a->ta + i;
}

int pop(int* a){

}
