#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s2_l2_list.h"
#include "s2_l2_vector.h"

int do_everything_vector(vpas** vect, list* l, int g){
	lpas* pq = l->first;
	int z = 0, time = 1;
	int* lengh = (int *)calloc(g, sizeof(int));
	int* ptime = (int *)calloc(g, sizeof(int));
	while(pq || z){
			if (time > 1){
				pop_vector(vect, time, g, lengh, ptime);
			}
			while (pq && pq->ta == time){
				push_vector(vect, pq, time, g, lengh, ptime);
				pq = pq->next;
			}
			for (int v = 0; v < g; v ++){
				if (lengh[v] > 0){
					z = 1;
					break;
				}
				else z = 0;
			}
			time ++;
		}
		delete_vector(vect, g, lengh, ptime);
		return 0;
}

int push_vector(vpas** vect, lpas* pq, int time, int g, int* lengh, int* ptime){
	int k = 100000, r;
        for (int l = 0; l < g; l++){
        	if (ptime[l] < k){
                	k = ptime[l];
                  	r = l;
                }
        }
	if (lengh[r] == 2){
		printf("Sorry, queue is full.\n");
		return 1;
	}
	vect[r][lengh[r]].id = pq->id;
	vect[r][lengh[r]].ta = pq->ta;
	vect[r][lengh[r]].ts = pq->ts;
	lengh[r] ++;
	ptime[r] += pq->ts;
	read_vector(vect, time, lengh, g);
	return 0;
}

void pop_vector(vpas** vect, int time, int g, int* lengh, int* ptime){
	for (int r = 0; r < g; r ++){
		while (lengh[r] > 0 && vect[r][0].ta + vect[r][0].ts == time){
			for (int i = 0; i < lengh[r] - 1; i ++){
				vect[r][i] = vect[r][i + 1];
			}
			ptime[r] -= vect[r][0].ts;
			lengh[r] --;
			read_vector(vect, time, lengh, g);
		}
        }
}

void read_vector(vpas** vect, int time, int* lengh, int g){
	printf("Time is %d.\n", time);
	for (int i = 0; i < g; i ++){
		printf("Stand %d: ", i + 1);
		if (lengh[i] > 0){
			for (int j = 0; j < lengh[i]; j ++){
				printf("%s ", vect[i][j].id);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void delete_vector(vpas** vect, int g, int* ptime, int* lengh){
	for (int i = 0; i < g; i ++){
		free(vect[i]);
	}
	free(lengh);
	free(ptime);
	free(vect);
}
