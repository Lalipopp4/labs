#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s2_l2_struct.h"
#include "s2_l2_list.h"
#include "s2_l2_vector.h"

int main(int argc, char const* argv[]){
	int g;
	list* l = new_list(l);
	printf("Enter number of stands: ");
	scanf("%d", &g);
    	if (argc == 1){
		queue* q = (queue *)calloc(1, sizeof(queue));q->sts = g;
		q->st = (stand * )calloc(q->sts, sizeof(stand));
		if (q->sts == 0){
			free(q);
			return 1;
		}
		do_everything_list(q, l);
	}
	else{
		vpas** vect = (vpas **)calloc(g, sizeof(vpas *));
		for (int i = 0; i < g; i ++){
			vect[i] = (vpas *)malloc(2 * sizeof(vpas));
		}
		do_everything_vector(vect, l, g);
	}
	delete_list(l);
	printf("Good bye\n");
	return 0;
}
