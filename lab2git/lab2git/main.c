#include <stdio.h>
#include <stdlib.h>

int main()
{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"

int main(){
	int h, f = 0;
	char c;
	int fl = 1;
	do{
		if (f == 1) printf("Try again.\n");
		printf("What do you want to use?\n");
		printf("1) Structure.\n");
		printf("2) Vector.\n");
		scanf("%d%*c", &h);

	}while(f);
    if (h == 1){
			queue* q;
			printf("Enter number of stands.\n");
			scanf("%d%*c", &q->sts);
			if (q->sts == 0) return 1;
			q = (queue *)calloc(1, sizeof(queue));
			for (int j = 0; j < q->sts; j ++){
				q->st[j].lengh = 0;
			}
			int i = 0, k = 1, time = 1, t = 0;
			int m,v;
			char c;
			pas* first;
			char* str = (char *)malloc(sizeof(char));
			printf("Enter id/ta/ts: ");
			scanf("%c", &c);
			do{
				while (c != '/'){
					str[i] = c;
					i++;
					str = (char *)realloc(str, i + 1);
					scanf("%c", &c);
				}
				i = 0;
				scanf("%d%*c%d", &m, &v);
				for (int o = 0; o < q->sts; o ++){
					if (q->st[o]->pas.ta + q->st[o]->pas.ts == time){
						pop_struct(q->st[o]->pas);
					}
                }
                for (int l = 0; l < q->sts; l++){
                    if (q->st[l].lengh < k){
                        k = q->st[l].lengh;
                        m = l;
                    }
                }
				if (t == 0){
					q->st = p;
					t = 1;
				}

				p->next = (lpas *)calloc(1,sizeof(lpas));
				ff = p;
				p = p->next;
				scanf("%c", &c);
				if (c != '\n'){
					scanf("%c", &c);}
				else{
					printf("ff\n");
					free(p);
					p = NULL;
				}
			}while (c != '\n');

			/*
			while(pp->next){
				while(pp->ta == time){

					q->st[m].pas[q->st[i].lengh].id = pp->id;
					q->st[m].pas[q->st[i].lengh].ta = pp->ta;
					q->st[m].pas[q->st[i].lengh].ts = pp->ts;
					q->st[m].lengh += q->st[m].pas[q->st[i].lengh].ts;
				}
			}*/
			f = 0;}
		else if (h == 2){
            printf("pause\n");
		}
		else f = 1;

	lpas* pq = top;
	while(pq){
		free(pq->id);
                free(pq);
                pq = pq->next;
	}
	free(l);
	printf("Good bye\n");
	return 0;
}
}
