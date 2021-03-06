#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "list.h"

int main(){
	int h, f = 0;
	int fl = 1;
	do{
		if (f == 1) printf("Try again.\n");
		printf("What do you want to use?\n");
		printf("1) Structure.\n");
		printf("2) Vector.\n");
		scanf("%d%*c", &h);
		if (h != 1 && h != 2) f = 1;
		else f = 0;
	}while(f);
	char c;
	list* l = (list *)calloc(1, sizeof(list));
	lpas* p = (lpas *)malloc(sizeof(pas));
	lpas* first;
	int i = 0, m, v, t = 0;
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
			first = p;
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
    if (h == 1){
		queue* q;
		q = (queue *)calloc(1, sizeof(queue));
		printf("Enter number of stands.\n");
		scanf("%d%*c", &q->sts);
		if (q->sts == 0){
			free(q);
			return 1;
		}
		q->st = (stand * )calloc(q->sts, sizeof(stand));
		for (int j = 0; j < q->sts; j ++){
			q->st[j].lengh = 0;
		}
		int i = 0, k = 1, time = 1, t = 0, u = 0, z = 0;
		lpas* pq = first;
		while(pq || z){
			if (time > 1){
				for (int o = 0; o < q->sts; o ++){
					if (q->st[o].first->ta + q->st[o].first->ts == time){
							pop_struct(q->st, o);
							read_struct(q, time);
						}
                			}
			}
			while (pq && pq->ta == time){
                		for (int l = 0; l < q->sts; l++){
                    			if (q->st[l].lengh < k){
                       				k = q->st[l].lengh;
                        			u = l;
                    			}
                		}
				push_struct1(q, u, pq);
				read_struct(q, time);
				pq = pq->next;
			}
			for (int v = 0; v < q->sts; v ++){
				if (q->st[v].lengh > 0){
					z = 1;
					break;
				}
				else z = 0;
			}
			time ++;
    }
	f = 0;
	free(q->st);
	free(q);}
		else if (h == 2){
            printf("pause\n");
		}
	lpas* pq = first;
	while(pq){
		free(pq->id);
                free(pq);
                pq = pq->next;
	}

	free(l);
	printf("Good bye\n");
	return 0;
}
