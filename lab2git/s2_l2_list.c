#include "s2_l2_list.h"

#include <stdlib.h>
#include <stdio.h>

list* new_list(list* l){
	l = (list *)calloc(1, sizeof(list));
	lpas* p = (lpas *)malloc(sizeof(lpas));
	int i = 0, t = 0;
	char c;
	printf("Enter id/ta/ts: ");
	scanf("%c", &c);
	do{
		p->id = (char *)malloc(sizeof(char));
		while (c != '/'){
			p->id[i] = c;
			i++;
			p->id = (char *)realloc(p->id, i + 1);
			scanf("%c", &c);
		}
		if (t == 0){
			l->first = p;
			t = 1;
		}
		i = 0;
		scanf("%d%*c%d", &p->ta, &p->ts);
		scanf("%c", &c);
		if (c != '\n'){
			scanf("%c", &c);
			p->next = (lpas *)malloc(sizeof(lpas));
			p = p->next;
		}
		else{
			p->next = NULL;
		}
	}while (c != '\n');
	return l;
}

void delete_list(list* l){
	lpas* pq = l->first;
	lpas* pp;
	while(pq){
		pp = pq->next;
		free(pq->id);
                free(pq);
                pq = pp;
	}
	free(l);
}
