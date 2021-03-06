#include "test.h"
#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void push_struct(stand* a, int r, lpas* pq){
	if (a[r].lengh == 0){
		a[r].first = a->pas;
	}
	a[r].lengh += 1;
	a[r].time += pq->ts;
	a[r].pas = (pas *)malloc(sizeof(pas));
	a[r].pas->id = pq->id;
	a[r].pas->ta = pq->ta;
	a[r].pas->ts = pq->ts;
	printf("_%s_%d_\n", a[r].pas->id, r);
	a[r].pas = a[r].pas->next;
}

void push_struct1(queue* q, int r, lpas* pq){
	q->st[r].pas = (pas *)malloc(sizeof(pas));
	q->st[r].pas->id = pq->id;
	q->st[r].pas->ta = pq->ta;
	q->st[r].pas->ts = pq->ts;
	if (q->st[r].lengh == 0){
		q->st[r].first = q->st[r].pas;
	}
	q->st[r].lengh += 1;
	q->st[r].time += pq->ts;

	printf("_%s_%d_\n", q->st[r].pas->id, r);
	q->st[r].last = q->st[r].pas;
	q->st[r].pas = q->st[r].pas->next;
}

void pop_struct(queue, int r){
	puts("RvR");
	a[r].first = a[r].pas->next;
	puts("RwR");
	a[r].time -= a[r].pas->ts;
	puts("RaR");
	free(a[r].pas);
	puts("RtR");
	a[r].lengh--;
}

void read_struct(queue* q, int time){
	printf("Time is %d.\n", time);
	pas* pqe = q->st[0].first;
	printf("=%s=\n", pqe->id);
	for (int i = 0; i < q->sts; i ++){
		printf("Stand %d: ", i + 1);
		pas* pq = q->st[i].first;
		while(pq){
			printf("%s ", pq->id);
			pq = pq->next;
		}
		printf("\n");
	}
}
