#include "s2_l2_struct.h"
#include "s2_l2_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_struct(queue* q){
	for (int j = 0; j < q->sts; j ++){
		q->st[j].lengh = 0;
		q->st[j].pas = (pas *)malloc(sizeof(pas));
	}
}

int do_everything_list(queue* q, list* l){
		init_struct(q);
		int time = 1, z = 0;
		lpas* pq = l->first;
		while(pq || z){
			if (time > 1){
				pop_struct(q, time);
			}
			while (pq && pq->ta == time){
				push_struct(q, pq, time);
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
		delete_struct(q);
		return 0;
}

void push_struct(queue* q, lpas* pq, int time){
	int k = 100000, r;
        for (int l = 0; l < q->sts; l++){
                if (q->st[l].time < k){
                	k = q->st[l].time;
                  	r = l;
                }
        }
	q->st[r].pas->id = pq->id;
	q->st[r].pas->ta = pq->ta;
	q->st[r].pas->ts = pq->ts;
	if (q->st[r].lengh == 0){
		q->st[r].first = q->st[r].pas;
	}
	q->st[r].lengh += 1;
	q->st[r].time += pq->ts;
	q->st[r].last = q->st[r].pas;
	q->st[r].pas->next = (pas *)malloc(sizeof(pas));
	q->st[r].pas = q->st[r].pas->next;
	read_struct(q, time);
}



void pop_struct(queue* q, int time){
	stand* a = q->st;
	for (int r = 0; r < q->sts; r ++){
		while (a[r].lengh > 0 && a[r].first->ta + a[r].first->ts == time){
			pas* p = a[r].first;
			a[r].first = p->next;
			a[r].time -= p->ts;
			a[r].lengh--;
			free(p);
			p = NULL;
			read_struct(q, time);
		}
        }
}

void read_struct(queue* q, int time){
	printf("Time is %d.\n", time);
	for (int i = 0; i < q->sts; i ++){
		printf("Stand %d: ", i + 1);
		if (q->st[i].lengh > 0){
			pas* pq = q->st[i].first;
			for (int j = 0; j < q->st[i].lengh; j ++){
				printf("%s ", pq->id);
				pq = pq->next;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void delete_struct(queue* q){
	for (int i = 0; i < q->sts; i ++){
		free(q->st[i].first);
	}
	free(q->st);
	free(q);
}
